#include <iostream>

using namespace std;

bool matchCore(char *s1, char *s2)
{
    if (*s1 == '\0' && *s2 == '\0')
        return true;

    if (*s1 != '\0' && *s2 == '\0')   // 字符串的全部字符要与模式相匹配
        return false;

    // 当下一个字符是'*'
    if (*(s2 + 1) == '*')
    {
        if (*s1 == *s2 || (*s2 == '.' && *s1 != '\0'))   // 相等的两种情况：要么字符一样，与要么模板的这个位置是'.'
            return matchCore(s1 + 1, s2)       ||    // 第一种类型: 继续匹配s1的下一个字符
                    matchCore(s1 + 1, s2 + 2)  ||    // 第二种类型: 只有当前位置匹配，也就是'*'只相当于重复前面的字符只有一次
                    matchCore(s1, s2 + 2);           // 第三种类型: 忽略这个'*', 感觉这种情况可以省略，因为此时不会有*s1 == *s2
        else
            return matchCore(s1, s2+2);    // 忽略这个'*'
    }
    if (*s1 == *s2 || (*s2 == '.' && *s1 != '\0'))   // 判断两个字符相等的情况的两种条件，同上
        return matchCore(s1 + 1, s2 + 1);

    return false;
}

// s1: 输入的待匹配的字符串，s2: 正则表达式
bool isMatch(char *s1, char *s2)
{
    // 输入判断
    if (s1 == nullptr || s2 == nullptr)
        return false;

    return matchCore(s1, s2);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    string s1, s2;
    cin >> s1 >> s2;

    cout << isMatch(const_cast<char*>(s1.c_str()), const_cast<char *>(s2.c_str())) << endl;

    return 0;
}
