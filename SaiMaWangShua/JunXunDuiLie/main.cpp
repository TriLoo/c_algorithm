#include <iostream>
#include <vector>

using namespace std;

void getLast(const int nums) {
    if (nums <= 3) {
        for (int i = 1; i < nums; ++i)
            cout << i << " ";
        cout << nums << endl;
    }

    vector<int> namelist(nums, 1);

    int removelist = 0;
    int removetotal = 0;
    int step = 0;
    while(nums - removetotal > 3)
    {
        for (int i = 0; i < nums; ++i)
        {
            if(namelist.at(i) != 0)
            {
                ++step;
                if(step == 2)
                {
                    namelist.at(i) = 0;
                    ++removelist;
                    step = 0;
                }
            }
        }
        removetotal += removelist;
        removelist = 0;
        step = 0;

        if(nums-removetotal <= 3)
            break;

        for (int i = 0; i < nums; ++i)
        {
            if(namelist.at(i) != 0)
            {
                ++step;
                if (step == 3)
                {
                    namelist.at(i) = 0;
                    ++removelist;
                    step = 0;
                }
            }
        }
        removetotal += removelist;
        removelist = 0;
        step = 0;
    }

    for (int i = 0; i < nums; ++i)
    {
        if (namelist.at(i) != 0)
            cout << i+1 << " ";
    }
    cout << endl;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N = 0;
    cin >> N;

    vector<int> studentNums(N, 0);
    int temp = 0;
    for (int i = 0; i < N; ++i)
    {
        cin >> temp;
        studentNums.at(i) = temp;
        //cin >> studentNums.at(i);   // at() returns a reference to the element at position i in the vector
    }

    for (int i = 0; i < N; ++i)
        getLast(studentNums.at(i));

    return 0;
}
