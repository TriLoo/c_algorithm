#include <iostream>
#include "fstream"

#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

#include "Eigen/Geometry"
#include "boost/format.hpp"  // for formating string
#include "pcl/point_types.h"
#include "pcl/io/pcd_io.h"
#include "pcl/visualization/pcl_visualizer.h"

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<Mat> colorImgs, depthImgs;   // 彩色图和深度图
    vector<Eigen::Isometry3d> poses;    // 相机位姿

    ifstream fin("./pose.txt");
    if(!fin)
    {
        cerr << "Read pose.txt failed..." << endl;
        return -1;
    }

    for(int i = 0; i < 5; ++i)
    {
        boost::format fmt("./%s/%d.%s");   // 图像格式
        colorImgs.push_back(imread((fmt%"color"%(i+1)%"png").str()));

        depthImgs.push_back(imread((fmt%"depth"%(i+1)%"pgm").str(), -1));  // 使用-1读取原图像

        double data[7] = {0};
        for(auto & d : data)
            fin >> d;

        Eigen::Quaterniond q(data[6], data[3], data[4], data[5]);   // 构造四元数

        Eigen::Isometry3d T(q);

        T.pretranslate(Eigen::Vector3d(data[0], data[1], data[2]));  // 构造偏移向量

        poses.push_back(T);
    }

    // 计算点云并拼接
    // 相机内参
    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;

    cout << "正在将图像转换成点云" << endl;

    // 定义点云使用的数据格式
    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;

    // 新建一个点云
    PointCloud::Ptr pointCloud(new PointCloud);

    for(int i = 0; i < 5; i++)
    {
        cout << "转换图像中" << endl;
        Mat color = colorImgs[i];
        Mat depth = depthImgs[i];
        Eigen::Isometry3d T = poses[i];

        for(int v = 0; v < color.rows; v++)
            for(int u = 0; u < color.cols; u++)
            {
                unsigned int d = depth.ptr<unsigned short>( v )[u]; // 深度值
                if(d == 0)
                    continue;   // 为0， 表示没测量到
                Eigen::Vector3d point;
                point[2] = double(d) / depthScale;
                point[0] = (u - cx) * point[2] / fx;
                point[1] = (v - cy) * point[2] / fy;
                Eigen::Vector3d pointWorld = T * point;

                PointT p;
                p.x = pointWorld[0];
                p.y = pointWorld[1];
                p.z = pointWorld[2];

                p.b = color.data[v * color.step + u * color.channels()];
                p.g = color.data[v * color.step + u * color.channels() + 1];
                p.r = color.data[v * color.step + u * color.channels() + 2];

                pointCloud->points.push_back(p);
            }
    }

    pointCloud->is_dense = false;
    cout << "点云共有" << pointCloud->size() << " 个点。" << endl;
    pcl::io::savePCDFileBinary("map.pcd", *pointCloud);

    return 0;
}
