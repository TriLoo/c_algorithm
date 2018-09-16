#include <iostream>

using namespace std;

string str_copy(string &s)
{
    string ret;
    for(auto &ele : s)
        ret.push_back(ele);

    return ret;
}

int main() {
    string sins;
    cin >> sins;

    cout << str_copy(sins) << endl;

    return 0;
}
