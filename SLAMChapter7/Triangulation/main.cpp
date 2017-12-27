#include <iostream>
#include "vector"
#include "cassert"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace std;
using namespace cv;

/*
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
*/
void find_feature_matches ( const Mat& img_1, const Mat& img_2,
                            std::vector<KeyPoint>& keypoints_1,
                            std::vector<KeyPoint>& keypoints_2,
                            std::vector< DMatch >& matches )
{
    //-- 初始化
    Mat descriptors_1, descriptors_2;
    // used in OpenCV3
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    // use this if you are in OpenCV2
    // Ptr<FeatureDetector> detector = FeatureDetector::create ( "ORB" );
    // Ptr<DescriptorExtractor> descriptor = DescriptorExtractor::create ( "ORB" );
    Ptr<DescriptorMatcher> matcher  = DescriptorMatcher::create ( "BruteForce-Hamming" );
    //-- 第一步:检测 Oriented FAST 角点位置
    detector->detect ( img_1,keypoints_1 );
    detector->detect ( img_2,keypoints_2 );

    //-- 第二步:根据角点位置计算 BRIEF 描述子
    descriptor->compute ( img_1, keypoints_1, descriptors_1 );
    descriptor->compute ( img_2, keypoints_2, descriptors_2 );

    //-- 第三步:对两幅图像中的BRIEF描述子进行匹配，使用 Hamming 距离
    vector<DMatch> match;
    //BFMatcher matcher ( NORM_HAMMING );
    matcher->match ( descriptors_1, descriptors_2, match );

    //-- 第四步:匹配点对筛选
    double min_dist=10000, max_dist=0;

    //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = match[i].distance;
        if ( dist < min_dist ) min_dist = dist;
        if ( dist > max_dist ) max_dist = dist;
    }

    printf ( "-- Max dist : %f \n", max_dist );
    printf ( "-- Min dist : %f \n", min_dist );

    //当描述子之间的距离大于两倍的最小距离时,即认为匹配有误.但有时候最小距离会非常小,设置一个经验值30作为下限.
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        if ( match[i].distance <= max ( 2*min_dist, 30.0 ) )
        {
            matches.push_back ( match[i] );
        }
    }
}

// K is 相机内参
/*
Point2d pixel2cam(const Point2d &p, const Mat &K)
{
    return Point2d((p.x - K.at<double>(0, 2))/K.at<double>(0, 0),
                   (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1));
}
 */
Point2d pixel2cam ( const Point2d& p, const Mat& K )
{
    return Point2d
           (
               ( p.x - K.at<double> ( 0,2 ) ) / K.at<double> ( 0,0 ),
               ( p.y - K.at<double> ( 1,2 ) ) / K.at<double> ( 1,1 )
           );
}

/*
void pose_estimation_2d2d(
        const vector<KeyPoint>& ky1,
        const vector<KeyPoint>& ky2,
        const vector<DMatch>& matches,
        Mat &R, Mat &t
)
{
    // 相机内参
    Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);

    // Point2d 保存 像素坐标
    vector<Point2d> points1, points2;
    for(int i = 0; i < (int)matches.size(); ++i)
    {
        points1.push_back(ky1[matches[i].queryIdx].pt);
        points2.push_back(ky2[matches[i].trainIdx].pt);
    }

    // 计算基础矩阵： p2^T F p1 = 0
    Mat fundamentalMat = findFundamentalMat(points1, points2, CV_FM_8POINT);   // 八点法

    Point2d pp(325.1, 249.7);
    int focallen = 521;

    // 计算本质矩阵
    Mat essentialMat = findEssentialMat(points1, points2, K, RANSAC, 0.999, 1.0);
    //Mat essentialMat = findEssentialMat(points1, points2, focallen, pp, RANSAC, 0.999, 1.0);

    // 计算单应矩阵
    Mat homographyMat = findHomography(points1, points2, RANSAC, 3, noArray(), 2000, 0.99);

    // 从本质矩阵计算R, t
    recoverPose(essentialMat, points1, points2, K, R, t);

    // Test, R, t 是第二幅图像相对于第一幅图像的估计
    //cout << "R = " << R << endl;
    //cout << "t = " << t << endl;
}
*/
void pose_estimation_2d2d ( std::vector<KeyPoint> keypoints_1,
                            std::vector<KeyPoint> keypoints_2,
                            std::vector< DMatch > matches,
                            Mat& R, Mat& t )
{
    // 相机内参,TUM Freiburg2
    Mat K = ( Mat_<double> ( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );

    //-- 把匹配点转换为vector<Point2f>的形式
    vector<Point2f> points1;
    vector<Point2f> points2;

    for ( int i = 0; i < ( int ) matches.size(); i++ )
    {
        points1.push_back ( keypoints_1[matches[i].queryIdx].pt );
        points2.push_back ( keypoints_2[matches[i].trainIdx].pt );
    }

    //-- 计算基础矩阵
    Mat fundamental_matrix;
    fundamental_matrix = findFundamentalMat ( points1, points2, CV_FM_8POINT );
    cout<<"fundamental_matrix is "<<endl<< fundamental_matrix<<endl;

    //-- 计算本质矩阵
    Point2d principal_point ( 325.1, 249.7 );	//相机光心, TUM dataset标定值
    double focal_length = 521;			//相机焦距, TUM dataset标定值
    Mat essential_matrix;
    essential_matrix = findEssentialMat ( points1, points2, focal_length, principal_point );
    cout<<"essential_matrix is "<<endl<< essential_matrix<<endl;

    //-- 计算单应矩阵
    Mat homography_matrix;
    homography_matrix = findHomography ( points1, points2, RANSAC, 3 );
    cout<<"homography_matrix is "<<endl<<homography_matrix<<endl;

    //-- 从本质矩阵中恢复旋转和平移信息.
    recoverPose ( essential_matrix, points1, points2, R, t, focal_length, principal_point );
    cout<<"R is "<<endl<<R<<endl;
    cout<<"t is "<<endl<<t<<endl;

}

// 三角测量：
// points，含有估计的三维坐标
/*
void triangulation(
    const vector<KeyPoint>& ky1,
    const vector<KeyPoint>& ky2,
    const vector<DMatch>& matches,
    const Mat& R,
    const Mat &t,
    vector<Point3d>& points
)
{
    // 准备[R | t]
    Mat T1 = (Mat_<float>(3, 4) <<
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0);
    // 相机运动估计
    Mat T2 =  (Mat_<float>(3, 4) <<
            R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2), t.at<double>(0, 0),
            R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2), t.at<double>(1, 0),
            R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2), t.at<double>(2, 0)
    );

    // 相机内参
    Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);

    // 用于存放像素坐标
    vector<Point2f> pts1, pts2;

    cout << "pts1.size = " << ky1.size() << endl;

    for (auto m : matches)
    {
        pts1.push_back(pixel2cam(ky1[m.queryIdx].pt, K));
        pts2.push_back(pixel2cam(ky2[m.trainIdx].pt, K));
    }

    cout << pts1.size() << endl;
    cout << pts1 << endl;

    // 三角化
    Mat pts;  // 保存4 × N 齐次性坐标
    triangulatePoints(T1, T2, pts1, pts2, pts);
    //cout << pts << endl;

    // 将齐次性坐标转换为非齐次坐标, 按列存储， 不同的列保存不同点的齐次三维坐标
    for (int j = 0; j < pts.cols; ++j) {
        Mat x = pts.col(j);
        x /= x.at<float>(3, 0);   // 归一化
        Point3d p(
                x.at<float>(0, 0),
                x.at<float>(1, 0),
                x.at<float>(2, 0)
        );

        //cout << p << endl;

        points.push_back(p);
    }
}
*/
void triangulation (
    const vector< KeyPoint >& keypoint_1,
    const vector< KeyPoint >& keypoint_2,
    const std::vector< DMatch >& matches,
    const Mat& R, const Mat& t,
    vector< Point3d >& points )
{
    Mat T1 = (Mat_<float> (3,4) <<
        1,0,0,0,
        0,1,0,0,
        0,0,1,0);
    Mat T2 = (Mat_<float> (3,4) <<
        R.at<double>(0,0), R.at<double>(0,1), R.at<double>(0,2), t.at<double>(0,0),
        R.at<double>(1,0), R.at<double>(1,1), R.at<double>(1,2), t.at<double>(1,0),
        R.at<double>(2,0), R.at<double>(2,1), R.at<double>(2,2), t.at<double>(2,0)
    );

    Mat K = ( Mat_<double> ( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );
    vector<Point2f> pts_1, pts_2;
    for ( DMatch m:matches )
    {
        // 将像素坐标转换至相机坐标
        pts_1.push_back ( pixel2cam( keypoint_1[m.queryIdx].pt, K) );
        pts_2.push_back ( pixel2cam( keypoint_2[m.trainIdx].pt, K) );
    }

    Mat pts_4d;
    cv::triangulatePoints( T1, T2, pts_1, pts_2, pts_4d );

    // 转换成非齐次坐标
    for ( int i=0; i<pts_4d.cols; i++ )
    {
        Mat x = pts_4d.col(i);
        x /= x.at<float>(3,0); // 归一化
        Point3d p (
            x.at<float>(0,0),
            x.at<float>(1,0),
            x.at<float>(2,0)
        );
        points.push_back( p );
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Mat imgA = imread("1.png", IMREAD_COLOR);
    Mat imgB = imread("2.png", IMREAD_COLOR);

    assert(imgA.empty() != true);
    assert(imgB.empty() != true);

    //Mat Descrip1, Descrip2;
    vector<KeyPoint> ky1, ky2;
    vector<DMatch> matches;

    find_feature_matches(imgA, imgB, ky1, ky2, matches);

    cout << "Success 1." << endl;

    Mat R, t;
    pose_estimation_2d2d(ky1, ky2, matches, R, t);

    cout << "Success 2." << endl;

    cout << "R = " << R << endl;
    cout << "t = " << t << endl;

    // 三角化
    vector<Point3d> points;  // 保存三维坐标
    triangulation(ky1, ky2, matches, R, t, points);

    cout << "Success 3." << endl;

    // 重投影测试
    // 相机内参
    Mat K = (Mat_<float>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);

    cout << "Success 4." << endl;

    for (int i = 0; i < matches.size(); ++i)
    {
        Point2d pt1_cam = pixel2cam(ky1[matches[i].queryIdx].pt, K);
        Point2d pt1_cam_3d(points[i].x / points[i].z, points[i].y / points[i].z);

        cout << "Point in the first camera frame: " << pt1_cam << endl;
        cout << "Point projected from 3d: " << pt1_cam_3d << ", d = " << points[i].z << endl;
    }

    return 0;
}