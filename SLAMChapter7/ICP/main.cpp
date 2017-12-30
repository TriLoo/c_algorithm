#include <iostream>
#include "vector"
#include "cassert"
#include "cmath"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "g2o/core/base_vertex.h"
#include "g2o/core/base_unary_edge.h"
#include "g2o/core/block_solver.h"
#include "g2o/core/optimization_algorithm_levenberg.h"
#include "g2o/solvers/csparse/linear_solver_csparse.h"
#include "g2o/types/sba/types_six_dof_expmap.h"


using namespace std;
using namespace cv;

void find_feature_matches(Mat &imgA, Mat imgB, vector<KeyPoint>& ky1, vector<KeyPoint> &ky2, vector<DMatch> &matches)
{
    // storing the descriptions
    Mat descrip1, descrip2;

    Ptr<Feature2D> detector = ORB::create();
    Ptr<DescriptorMatcher> descriptor = DescriptorMatcher::create("BruteForce-Hamming(2)");

    // detect the feature points
    detector->detect(imgA, ky1);
    detector->detect(imgB, ky2);

    // computer the description
    detector->compute(imgA, ky1, descrip1);
    detector->compute(imgB, ky2, descrip2);

    // calculate the match
    vector<DMatch> match;
    descriptor->match(descrip1, descrip2, match);

    // 筛选
    double min_dist = 10000, max_dist = 0;

    for(int i = 0; i < descrip1.rows; i++)
    {
        double dist = match[i].distance;
        if(min_dist > dist)
            min_dist = dist;
        if(max_dist < dist)
            max_dist = dist;
    }

    for (int i = 0; i < descrip1.rows; ++i) {
        double dist = match[i].distance;
        if(dist < max(2 * min_dist, 30.0))
            matches.push_back(match[i]);
    }

   // for test
   // Mat matchImg;
   // drawMatches(imgA, ky1, imgB, ky2, matches, matchImg);
   // imshow("Match", matchImg);

   // waitKey(0);
}
Point2d pixel2cam ( const Point2d& p, const Mat& K )
{
    return Point2d
           (
               ( p.x - K.at<double> ( 0,2 ) ) / K.at<double> ( 0,0 ),
               ( p.y - K.at<double> ( 1,2 ) ) / K.at<double> ( 1,1 )
           );
}

// pts*: 3D point
void poseEstimation3d3d(
        const vector<Point3f> &ptsA,
        const vector<Point3f> &ptsB,
        Mat &R, Mat &t
)
{
    // 保存均值
    Point3f meanA(0, 0, 0);
    Point3f meanB(0, 0, 0);
    int N = ptsA.size();
    for (int i = 0; i < N; ++i)
    {
        meanA += ptsA[i];
        meanB += ptsB[i];
    }
    //meanA /= N;
    //meanB /= N;
    meanA = Point3f(Vec3f(meanA) / N);
    meanB = Point3f(Vec3f(meanB) / N);

    // 将每个点中心化
    vector<Point3f> q1(0), q2(0);
    //cout << "N = " << N << endl;    // For test
    for (int j = 0; j < N; ++j) {
        q1.push_back(ptsA[j] - meanA);
        q2.push_back(ptsB[j] - meanB);
        //q1[j] = ptsA[j] - meanA;
        //q2[j] = ptsB[j] - meanB;
    }
    //cout << "N = " << q1.size() << endl;    // For test

    // 计算 W(3, 3) 矩阵
    Eigen::Matrix3d W = Eigen::Matrix3d::Zero();
    for (int k = 0; k < N; ++k)
    {
        W += Eigen::Vector3d(q1[k].x, q1[k].y, q1[k].z) * Eigen::Vector3d(q2[k].x, q2[k].y, q2[k].z).transpose();
    }

    // 计算W的SVD分解
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(W, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix3d U = svd.matrixU();
    Eigen::Matrix3d V = svd.matrixV();

    // 计算旋转矩阵R = UV^T
    Eigen::Matrix3d R_ = U * (V.transpose());
    Eigen::Vector3d t_ = Eigen::Vector3d(meanA.x, meanA.y, meanA.z) - R_ * Eigen::Vector3d(meanB.x, meanB.y, meanB.z);

    // Convert the R_ to Mat
    R = (Mat_<double>(3, 3) <<
            R_(0, 0), R_(0, 1), R_(0, 2),
            R_(1, 0), R_(1, 1), R_(1, 2),
            R_(2, 0), R_(2, 1), R_(2, 2)
    );
    t = (Mat_<double>(3, 1) << t_(0, 0), t_(1, 0), t_(2, 0));
}

// define G2O edge
class EdgeProjectXYZRGBDPoseOnly : public g2o::BaseUnaryEdge<3, Eigen::Vector3d, g2o::VertexSE3Expmap>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    EdgeProjectXYZRGBDPoseOnly(const Eigen::Vector3d &point) : _point(point){}

    virtual void computeError()
    {
        const g2o::VertexSE3Expmap* pose = static_cast<const g2o::VertexSE3Expmap *>(_vertices[0]);
        _error = _measurement - pose->estimate().map(_point);
    }

    virtual void linearizeOplus()
    {
        g2o::VertexSE3Expmap* pose = static_cast<g2o::VertexSE3Expmap* >(_vertices[0]);
        g2o::SE3Quat T(pose->estimate());
        Eigen::Vector3d xyz_trans = T.map(_point);

        double x = xyz_trans[0];
        double y = xyz_trans[1];
        double z = xyz_trans[2];

        _jacobianOplusXi(0, 0) = 0;
        _jacobianOplusXi(0, 1) = -z;
        _jacobianOplusXi(0, 2) = y;
        _jacobianOplusXi(0, 3) = -1;
        _jacobianOplusXi(0, 4) = 0;
        _jacobianOplusXi(0, 5) = 0;

        _jacobianOplusXi(1, 0) = z;
        _jacobianOplusXi(1, 1) = 0;
        _jacobianOplusXi(1, 2) = -x;
        _jacobianOplusXi(1, 3) = 0;
        _jacobianOplusXi(1, 4) = -1;
        _jacobianOplusXi(1, 5) = 0;

        _jacobianOplusXi(2, 0) = -y;
        _jacobianOplusXi(2, 1) = x;
        _jacobianOplusXi(2, 2) = 0;
        _jacobianOplusXi(2, 3) = 0;
        _jacobianOplusXi(2, 4) = 0;
        _jacobianOplusXi(2, 5) = -1;
    }

    bool read(istream &in) {}
    bool write (ostream & out) const {}
private:
    Eigen::Vector3d _point;
};


// bundle Adjustment
void bundleAdjustment(
        const vector<Point3f>& ptsA,    // 相机坐标系下的三维坐标
        const vector<Point3f>& ptsB,    // 相机坐标系下的三维坐标
        Mat &R, Mat &t
)
{
    // 初始化g2o
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<6, 3>> Block;
    Block::LinearSolverType* linearSolver = new g2o::LinearSolverCSparse<Block::PoseMatrixType>();
    Block *solver_ptr = new Block(linearSolver);
    g2o::OptimizationAlgorithmLevenberg *solver = new g2o::OptimizationAlgorithmLevenberg(solver_ptr);
    g2o::SparseOptimizer optimizer;
    optimizer.setAlgorithm(solver);

    // 定义顶点, vertex
    Eigen::Matrix3d R_mat;
    R_mat <<
          R.at<double> ( 0,0 ), R.at<double> ( 0,1 ), R.at<double> ( 0,2 ),
          R.at<double> ( 1,0 ), R.at<double> ( 1,1 ), R.at<double> ( 1,2 ),
          R.at<double> ( 2,0 ), R.at<double> ( 2,1 ), R.at<double> ( 2,2 );

    g2o::VertexSE3Expmap* pose = new g2o::VertexSE3Expmap();   // Camera pose
    pose->setId(0);
    //pose->setEstimate(g2o::SE3Quat(Eigen::Matrix3d::Identity(), Eigen::Vector3d(0, 0, 0)));
    pose->setEstimate(g2o::SE3Quat(R_mat, Eigen::Vector3d(t.at<double>(0, 0), t.at<double>(1, 0), t.at<double>(2, 0))));
    optimizer.addVertex(pose);

    // edges
    int index = 1;
    vector<EdgeProjectXYZRGBDPoseOnly*> edges;
    for(size_t i = 0; i < ptsA.size(); ++i)
    {
        EdgeProjectXYZRGBDPoseOnly* edge = new EdgeProjectXYZRGBDPoseOnly(Eigen::Vector3d(ptsB[i].x, ptsB[i].y, ptsB[i].z));
        edge->setId(index);
        edge->setVertex(0, dynamic_cast<g2o::VertexSE3Expmap*>(pose));
        edge->setMeasurement(Eigen::Vector3d(ptsA[i].x, ptsA[i].y, ptsA[i].z));
        edge->setInformation(Eigen::Matrix3d::Identity() * 1e-4);
        optimizer.addEdge(edge);
        index++;
        edges.push_back(edge);
    }

    optimizer.setVerbose(true);
    optimizer.initializeOptimization();
    optimizer.optimize(10); // iteration = 10

    cout << "After optimization: " << endl;
    cout << "T=" << endl << Eigen::Isometry3d(pose->estimate()).matrix() << endl;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    //Mat img = imread("Barbara.jpg", IMREAD_ANYCOLOR);

    // 相机内参
    Mat K = ( Mat_<double>( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );

    //-- 读取图像
    Mat imgA = imread ( "1.png", CV_LOAD_IMAGE_COLOR );
    Mat imgB = imread ( "2.png", CV_LOAD_IMAGE_COLOR );

    vector<KeyPoint> ky1, ky2;
    vector<DMatch> matches;
    find_feature_matches ( imgA, imgB, ky1, ky2, matches );
    cout<<"一共找到了"<<matches.size() <<"组匹配点"<<endl;

    //-- 读取深度图
    // 16-bits
    Mat imgA_dep = imread("1_depth.png", IMREAD_UNCHANGED);
    Mat imgB_dep = imread("2_depth.png", IMREAD_UNCHANGED);

    // 保存相机坐标系下的空间坐标
    vector<Point3f> pts3dA;
    vector<Point3f> pts3dB;
    for(auto m : matches)
    {
        ushort dA = imgA_dep.ptr<ushort>( int(ky1[m.queryIdx].pt.y) )[ static_cast<int>(ky1[m.queryIdx].pt.x) ];
        ushort dB = imgB_dep.ptr<ushort>( int(ky2[m.trainIdx].pt.y) )[ static_cast<int>(ky2[m.trainIdx].pt.x) ];
        if(dA == 0 || dB == 0)
            continue;
        float ddA = dA / 1000.0;
        float ddB = dB / 1000.0;
        Point2f ptempA = pixel2cam(ky1[m.queryIdx].pt, K);
        Point2f ptempB = pixel2cam(ky2[m.trainIdx].pt, K);
        pts3dA.push_back(Point3f(ptempA.x * ddA, ptempA.y * ddA, ddA));
        pts3dB.push_back(Point3f(ptempB.x * ddB, ptempB.y * ddB, ddB));
    }

    // ICP calculation
    Mat R, t;
    poseEstimation3d3d(pts3dA, pts3dB, R, t);

    cout << "R = " << endl << R << endl;
    cout << "t = " << endl << t << endl;

    //-- use BA 优化
    //-- based on G2O
    bundleAdjustment(pts3dA, pts3dB, R, t);

    cout << "R = " << endl << R << endl;
    cout << "t = " << endl << t << endl;

    // verify p1 = R * p2 + t
    for (int i = 0; i < 5; ++i)
    {
        cout << "p1 = " << pts3dA[i] << endl;
        cout << "p2 = " << pts3dB[i] << endl;
        cout << "(R * p2 + t" << R * (Mat_<double>(3, 1) << pts3dB[i].x, pts3dB[i].y, pts3dB[i].z) + t << endl;

        cout << endl;
    }

    /*
    //-- 估计两张图像间运动
    Mat R,t;
    pose_estimation_2d2d ( keypoints_1, keypoints_2, matches, R, t );

    //-- 验证E=t^R*scale
    Mat t_x = ( Mat_<double>( 3,3 ) << 0, -t.at<double>( 2,0 ), t.at<double>( 1,0 ), t.at<double>( 2,0 ), 0, -t.at<double>( 0,0 ), -t.at<double>( 1.0 ), t.at<double>( 0,0 ), 0 );

    cout<<"t^R="<<endl<<t_x*R<<endl;

    //-- 验证对极约束
    for ( DMatch m: matches )
    {
        Point2d pt1 = pixel2cam ( keypoints_1[ m.queryIdx ].pt, K );
        Mat y1 = ( Mat_<double>( 3,1 ) << pt1.x, pt1.y, 1 );
        Point2d pt2 = pixel2cam ( keypoints_2[ m.trainIdx ].pt, K );
        Mat y2 = ( Mat_<double>( 3,1 ) << pt2.x, pt2.y, 1 );
        Mat d = y2.t() * t_x * R * y1;
        cout << "epipolar constraint = " << d << endl;
    }
    */

    waitKey(0);

    return 0;
}
