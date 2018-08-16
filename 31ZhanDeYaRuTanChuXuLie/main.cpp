/**
 * @author smh
 * @date 2018.08.16
 *
 * @brief 剑指offer第31题
 *   栈的压入、弹出序列
 *
 *   思路：
 *       1. 如果下一个弹出的数字刚好是栈顶的数字，那么就直接弹出；如果下一个弹出的数字不在栈顶，则把压栈序列中剩余的数字压入栈，直到
 *          下一个与位于弹出序列的栈顶相同的数字；如果所有输入序列的数都压入了但还没有找到下一个弹出的数字，那么弹出序列不可能是一个
 *          弹出序列。
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool judgeQueue(vector<int> &inqs, vector<int> &outqs)
{
    stack<int> stackData;
    int lenOut = outqs.size(), lenIn = inqs.size();
    int j = 0;
    for (int i = 0; i < lenOut; ++i)
    {
        while (stackData.empty() || stackData.top() != outqs.at(i))
        {
            if (j == lenIn)
                return false;
            stackData.push(inqs[j++]);
        }
        if(!stackData.empty() &&  stackData.top() == outqs.at(i))
        {
            stackData.pop();
            continue;
        }
    }

    return true;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N, M;
    cin >> N >> M;
    vector<int> inq(N, 0);
    vector<int> outq(M, 0);
    for (int i = 0; i < N; ++i)
        cin >> inq.at(i);
    for (int i = 0; i < M; ++i)
        cin >> outq.at(i);

    if (judgeQueue(inq, outq))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
