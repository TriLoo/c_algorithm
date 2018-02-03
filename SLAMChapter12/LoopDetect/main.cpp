#include <iostream>
#include "string"
#include "cassert"
#include "vector"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

#include "DBoW3/Vocabulary.h"

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<Mat> imgIns(0);
    for (int i = 1; i < 11; ++i)
    {
        string name = "../data/" + to_string(i) + ".png";
        cout << name << endl;
        Mat imgIn = imread(name, IMREAD_COLOR);
        assert(!imgIn.empty());
        imgIns.push_back(imgIn);
    }

    Ptr<Feature2D> detector = ORB::create();     // use default parameters
    vector<Mat> descriptors(0);
    for (int j = 1; j < 11; ++j)
    {
        vector<KeyPoint> keypoints(0);
        Mat descriptor;
        detector->detectAndCompute(imgIns[j], Mat(), keypoints, descriptor);
        descriptors.push_back(descriptor);
    }

    // Begin generate vocab
    DBoW3::Vocabulary vocab;
    vocab.create(descriptors);

    cout << "Vocabulary Information: " << vocab << endl;
    vocab.save("vocabulary.yml.gz");

    cout << "Done!" << endl;

    return 0;
}