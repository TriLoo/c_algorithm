/**
 * \author smh
 * \date 2018.08.13
 *
 * \brief 翻转字符串，但word不翻转
 *  剑指offer第58题
 */
#include <iostream>

using namespace std;

void reverseCore(string &a, int s, int e)
{
    while (s < e)
    {
        char c = a.at(s);
        a.at(s) = a.at(e);
        a.at(e) = c;
        ++s;
        --e;
    }
}

string flipString(string &a)
{
    int len = a.length();
    // reverse the whole string
    reverseCore(a, 0, len-1);
    cout << a << endl;

    // reverse back each word
    int start = 0;
    int end = 0;

    while (start < len)
    {
        if (end == len)
        {
            reverseCore(a, start, end-1);
            break;
        }
        else if(a.at(end) == ' ')
        {
            reverseCore(a, start, end-1);
            ++end;
            start = end;
        }
        else
            ++end;
    }
    return a;
}

int main() {
    string s;
    while(getline(cin, s))
    {
        cout << s.length() << endl;     // 不包括最后的'\0'

        if (s.length() == 0)
            exit(-1);

        cout << flipString(s) << endl;
    }

    return 0;
}
