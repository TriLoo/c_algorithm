#include <iostream>
#include "string"
#include "cassert"
#include "vector"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

#include "DBoW3/Vocabulary.h"
#include "DBoW3/DBoW3.h"

using namespace std;
using namespace cv;

void genVocabular(vector<Mat>& imgIns, DBoW3::Vocabulary& vocab)
{
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
    vocab.create(descriptors);

    cout << "Vocabulary Information: " << vocab << endl;
    vocab.save("vocabulary.yml.gz");

    cout << "Done!" << endl;
}

void similarityDetect(DBoW3::Vocabulary& vocab, vector<Mat>& imgIns)
{
    Ptr<Feature2D> detector = ORB::create();
    vector<Mat> descriptors;
    vector<KeyPoint> keypoints;
    for (int i = 0; i < imgIns.size(); ++i)
    {
        Mat descriptor;
        detector->detectAndCompute(imgIns[i], Mat(), keypoints, descriptor);
        descriptors.push_back(descriptor);
    }

    cout << "Size = " << imgIns.size() << endl;

    // compare the i-th image to j-th image
    for (int i = 0; i < imgIns.size(); ++i)
    {
        DBoW3::BowVector v1;
        vocab.transform(descriptors[i], v1);
        for (int j = i; j < imgIns.size(); ++j)
        {
            DBoW3::BowVector v2;
            vocab.transform(descriptors[j], v2);

            double s = vocab.score(v1, v2);
            cout << "Image " << i << " vs image " << j << " : " << s << endl;
        }
    }

    // compare to the database
    DBoW3::Database db(vocab, false, 0);
    for (int i = 0; i < imgIns.size(); ++i)
        db.add(descriptors[i]);
    cout << "Database Information: " << db << endl;

    for (int i = 0; i < imgIns.size(); ++i)
    {
        DBoW3::QueryResults ret;
        db.query(descriptors[i], ret, 3);
        cout << "Image " << i << " return " << ret << endl << endl;
    }

    cout << "Done!" << endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    /* ***************   Generate Vocabular  *****************
    vector<Mat> imgIns(0);
    for (int i = 1; i < 11; ++i)
    {
        string name = "../data/" + to_string(i) + ".png";
        cout << name << endl;
        Mat imgIn = imread(name, IMREAD_COLOR);
        assert(!imgIn.empty());
        imgIns.push_back(imgIn);
    }

    DBoW3::Vocabulary vocab;
    ***************   Generate Vocabular  ***************** */

    // begin similarity judgment
    vector<Mat> imgIns(0);
    for (int i = 1; i < 11; ++i)
    {
        string name = "../data/" + to_string(i) + ".png";
        cout << name << endl;
        Mat imgIn = imread(name, IMREAD_COLOR);
        assert(!imgIn.empty());
        imgIns.push_back(imgIn);
    }

    DBoW3::Vocabulary vocab;
    genVocabular(imgIns, vocab);

    //cout << "Begin generate vocab." << endl;
    //DBoW3::Vocabulary vocab("vocabulary.yml.gz");
    //cout << "Begin generate vocab." << endl;
    if (vocab.empty())
    {
        cerr << "Read vocabulary failed..." << endl;
        return EXIT_FAILURE;
    }

    similarityDetect(vocab, imgIns);

    return 0;
}