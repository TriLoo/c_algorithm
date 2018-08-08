#include <iostream>
#include <vector>

using namespace std;

int getMax(vector<int>& scores, int beg, int end)
{
    if (scores.size() <= beg || scores.size() <= end)
        return -1;

    int max = scores.at(beg);
    for (int i = beg; i <= end; ++i)
        if(max < scores.at(i))
            max = scores.at(i);

    return max;
}


int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N, M;
    while(cin >> N)
    {

        cin >> M;    // 学生个数、操作的数目

        vector<int> scores(N, 0);

        // 读入初始成绩
        for (int i = 0; i < N; ++i)
            cin >> scores.at(i);

        vector<int> values;

        // 修改
        char op;
        int a, b, t;
        for (int i = 0; i < M; ++i)
        {
            cin >> op;
            if (op == 'Q')
            {
                cin >> a >> b;
                if(a <= b)
                {
                    t = getMax(scores, a-1, b-1);
                    values.push_back(t);
                }
                else
                {
                    t = getMax(scores, b - 1, a - 1);
                    values.push_back(t);
                }
            }

            if (op == 'U')
            {
                cin >> a >> b;
                scores.at(a-1) = b;
            }
        }

        for (auto ele : values)
            cout << ele << endl;
    }

    return 0;
}
