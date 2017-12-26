#include <iostream>
#include "vector"
#include "cassert"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

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

// K is 相机内参
Point2d pixel2cam(const Point2d &p, const Mat &K)
{
    return Point2d((p.x - K.at<double>(0, 2))/K.at<double>(0, 0),
                   (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1));
}

void triangulation(

)

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



    return 0;
}