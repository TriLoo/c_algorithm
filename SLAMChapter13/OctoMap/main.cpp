#include <iostream>
#include "fstream"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "boost/format.hpp"
#include "octomap/octomap.h"
#include "Eigen/Geometry"

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<Mat> colorImgs, depthImgs;
    vector<Eigen::Isometry3d> poses;

    ifstream fin("../data/pose.txt");
    if (!fin)
    {
        cerr << "Read file failed..." << endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 5; ++i)
    {
        boost::format fmt("../data/%s/%d.%s");
        colorImgs.push_back(imread((fmt%"color"%(i+1)%"png").str()));
        depthImgs.push_back(imread((fmt%"depth"%(i+1)%"pgm).str(), IMREAD_UNCHANGED));

        double data[7] = {0};
        for (int j = 0; j < 7; ++j)
        {
            fin >> data[i];
        }
        Eigen::Quaterniond q(data[6], data[3], data[4], data[5]);
        Eigen::Isometry3d T(q);
        T.pretranslate(Eigen::Vector3d(data[0], data[1], data[2]));
        poses.push_back(T);
    }

    // 内参
    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;

    // begin transform into octotree map
    octomap::OcTree tree(0.05);

    for (int i = 0; i < 5; ++i)
    {
        Mat color = colorImgs[i];
        Mat depth = depthImgs[i];

        Eigen::Isometry3d T = poses[i];

        octomap::Pointcloud cloud;

        for (int v = 0; v < color.rows; ++v)
        {
            for (int u = 0; u < color.cols; ++u)
            {
                double d = depth.ptr(v)[u];
                if (d == 0)
                    continue;
                if (d > 7000)
                    continue;

                Eigen::Vector3d point;
                point[2] = d / depthScale;
                point[0] = (u  - cx) * point[2] / fx;
                point[1] = (v  - cy) * point[2] / fy;

                Eigen::Vector3d pointWorld = T * point;

                cloud.push_back(pointWorld[0], pointWorld[1], pointWorld[2]);
            }
        }
        tree.insertPointCloud(cloud, octomap::point3d(T(0, 3), T(1, 3), T(2, 3)));
    }

    tree.updateInnerOccupancy();
    cout << "Saving Octomap ..." << endl;
    tree.writeBinary("octomap.bt");

    return 0;
}