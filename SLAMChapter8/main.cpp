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
    for (int index = 0; index < 100; ++index)
    {
        fin >> time_depth >> rgb_file >> time_depth >> depth_file;
        color = imread(path_to_dataset + "/" + rgb_file);
        depth = imread(path_to_dataset + "/" + depth_file, -1);
    }

    return 0;
}
