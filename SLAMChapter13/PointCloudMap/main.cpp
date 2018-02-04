#include <iostream>
#include "fstream"
#include "vector"
#include "string"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Eigen/Geometry"
#include "boost/format.hpp"
#include "pcl/point_types.h"
#include "pcl/io/pcd_io.h"
#include "pcl/filters/voxel_grid.h"
#include "pcl/visualization/pcl_visualizer.h"
#include "pcl/filters/statistical_outlier_removal.h"

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;

    // read images and depth images
    vector<Mat> colorImgs(0), depthImgs(0);
    vector<Eigen::Isometry3d> poses(0);

    ifstream fin("../data/pose.txt");

    if (!fin)
    {
        cerr << "Cannot find pose file" << endl;
        return EXIT_FAILURE;
    }

    // total 5 images
    for (int i = 0; i < 5; ++i)
    {
        boost::format fmt("../data/%s/%d.%s");
        colorImgs.push_back(imread((fmt%"color"%(i+1)%"png").str()));
        depthImgs.push_back(imread((fmt%"depth"%(i+1)%"pgm").str(), IMREAD_UNCHANGED));

        double data[7] = {0};
        for (int j = 0; j < 7; ++j)
        {
            fin >> data[i];
        }

        Eigen::Quaterniond q(data[6], data[3], data[4], data[5]);    // 四元数
        Eigen::Isometry3d T(q);
        T.pretranslate(Eigen::Vector3d(data[0], data[1], data[2]));
        poses.push_back(T);
    }

    // 相机内参
    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;

    cout << "Tranform image to pointcloud." << endl;

    cout << "Color image col: " << colorImgs[0].cols << endl;
    cout << "Color image Channels: " << colorImgs[0].channels() << endl;
    cout << "Color image step: " << colorImgs[0].step << endl;

    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;

    PointCloud::Ptr pointCloud(new PointCloud);

    // Get the world coordinates  of input image
    for (int i = 0; i < 5; ++i)
    {
        PointCloud::Ptr current(new PointCloud);
        Mat color = colorImgs[i];
        Mat depth = colorImgs[i];
        Eigen::Isometry3d T = poses[i];
        for (int v = 0; v < color.rows; ++v)
        {
            for (int u = 0; u < color.cols; ++u)
            {
                unsigned int d = depth.ptr(v)[u];
                if (d == 0)
                    continue;
                if (d >= 7000)
                    continue;

                Eigen::Vector3d point;
                point[2] = static_cast<double>(d) / depthScale;
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

                current->points.push_back(p);
            }
        }

        PointCloud::Ptr tmp(new PointCloud);
        pcl::StatisticalOutlierRemoval<PointT> statistical_filter;
        statistical_filter.setMeanK(50);
        statistical_filter.setStddevMulThresh(1.0);
        statistical_filter.setInputCloud(current);

        statistical_filter.filter(*tmp);

        (*pointCloud) += *tmp;
    }

    pointCloud->is_dense = false;
    cout << "Total " << pointCloud->size() << " points." << endl;

    // voxel filter
    pcl::VoxelGrid<PointT> voxel_filter;
    voxel_filter.setLeafSize(0.01, 0.01, 0.01);
    PointCloud::Ptr tmp(new PointCloud);
    voxel_filter.setInputCloud(pointCloud);
    voxel_filter.filter(*tmp);

    tmp->swap(*pointCloud);

    cout << "After filter: " <<  pointCloud->size() << " points." << endl;
    pcl::io::savePCDFileBinary("map.pcd", *pointCloud);

    return 0;
}