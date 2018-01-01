#include <iostream>
#include "vector"
#include "fstream"
#include "list"
#include "vector"
#include "chrono"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/video/tracking.hpp"

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;

    string path_to_dataset = "./data";
    string associate_file = path_to_dataset + "/associate.txt";
    ifstream fin(associate_file);

    string rgb_file, depth_file, time_rgb, time_depth;
    list<cv::Point2f> keypoints;
    Mat color, depth, last_color;
    for (int index = 0; index < 10; ++index)
    {
        fin >> time_depth >> rgb_file >> time_depth >> depth_file;
        color = imread(path_to_dataset + "/" + rgb_file);
        depth = imread(path_to_dataset + "/" + depth_file, -1);

        if (index == 0)
        {
            Ptr<FastFeatureDetector> detector = FastFeatureDetector::create();
            vector<KeyPoint> kys;
            detector->detect(color, kys);

            for(auto ky : kys)
                keypoints.push_back(ky.pt);
            last_color = color;

            cout << "index == 0." << endl;

            continue;
        }

        cout << "index > 0." << endl;

        if (color.data == nullptr || depth.data == nullptr)
            continue;

        cout << "Read image success." << endl;

        vector<Point2f> prev_kys, next_kys;
        for(auto ky : keypoints)
            prev_kys.push_back(ky);
        vector<unsigned char> status;
        vector<float> error;

        calcOpticalFlowPyrLK(last_color, color, prev_kys, next_kys, status, error);

        int i = 0;
        for(auto iter = keypoints.begin(); iter != keypoints.end(); i++)
        {
            if (status[i] == 0)
            {
                iter = keypoints.erase(iter);
                continue;
            }
            *iter = next_kys[i];
            iter++;
        }

        cout << "Tracked keypoints: " << keypoints.size() << endl;

        if (keypoints.size() == 0)
        {
            cout << "All keypoints are lost. " << endl;
            break;
        }

        Mat img_show = color.clone();
        for(auto kp : keypoints)
            circle(img_show, kp, 10, cv::Scalar(0, 240, 0), 1);
        imshow("Corners", img_show);
        waitKey(0);

        last_color = color;
    }

    return 0;
}
