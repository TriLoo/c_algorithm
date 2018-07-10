#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
// using for...each + regular expression
float getProb(const string &hist, const string & stars)
{
    string ins = hist;
    auto f = [](char a){};
    for_each(ins.begin(), ins.end(), f);

    size_t totallen = ins.length();
    int templen = 0;

    for (int i = 0; i < totallen; ++i)
        if (ins.at(i) == stars.at(i))
            ++templen;

    return static_cast<float>(templen) / totallen;
}
*/

float getProb(const string &hist, const string & stars)
{
    string ins = hist;
    size_t totalLen = hist.length();

    // convert the hist to a 01 string
    string conv;
    for (int i = 0; i < totalLen; ++i)
    {
        char sc = ins.at(i);
        if((sc <= 'z' && sc >= 'a') || (sc <= 'Z' && sc >= 'A'))
            sc = '1';
        else if(sc <= '9' && sc >= '0')
            sc = '1';
        else
            sc = '0';

        ins.at(i) = sc;
    }

    int tempLen = 0;
    for (int i = 0; i < totalLen; ++i)
    {
        if(stars.at(i) == ins.at(i))
            ++tempLen;
    }

    return tempLen * 1.0 / totalLen;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    string s1, s2;
    cin >> s1 >> s2;

    float prob = getProb(s1, s2) * 100;

    cout << fixed << setprecision(2) << prob << "%" << endl;

    return 0;
}
