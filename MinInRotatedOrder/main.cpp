#include <iostream>
//#include "memory"
#include "random"
#include "ctime"
#include "algorithm"

using namespace std;

class QuickSort
{
public:
    QuickSort(int *d, int len):aux(new int [len]())
    {
        for (int i = 0; i < len; ++i)
            aux[i] = d[i];
    }
    ~QuickSort() {delete [] aux;}
    //QuickSort(int *d): aux(d){}
    //~QuickSort(){}

    int Partion(int *data, int lo, int hi);
    void qc(int data[], int lo, int hi);
    void qc(int data[], int len);
private:
    void exch(int *d, int i, int j);
    int *aux;
};

void QuickSort::exch(int *d, int i, int j)
{
    if (i == j)
        return;

    int t = d[i];
    d[i] = d[j];
    d[j] = t;
}

int QuickSort::Partion(int *data, int lo, int hi)
{
    //static default_random_engine e(time(0));
    //static uniform_int_distribution<int> u(lo, hi);

    //int p = u(e);
    //cout << p << endl;

    int com = data[lo];
    int i = lo, j = hi + 1;

    while(true)
    {
        //while(less<int>(aux[++i], static_cast<int>(com)));
        while(data[++i] < com)
            if( i == hi)
                break;
        while(data[--j] > com)
            if (j == lo)
                break;
        if(i >= j)
            break;
        exch(data, i, j);
    }

    exch(data, lo, j);

    return j;
}

void QuickSort::qc(int *data, int len)
{
    if (len == 0)
        return;
    else
    {
        int mid = len >> 1;
        //int mid = Partion(0, len);    // 可能包含len, 即mid == len : True
        //if (mid == len)
           // mid = len >> 1;

        qc(data, 0, len);
    }
}

void QuickSort::qc(int *data, int lo, int hi)
{
    if (lo >= hi)
        return ;

    int j = Partion(data, lo, hi);
    cout << j << endl;
    qc(data, lo, j - 1);
    qc(data, j + 1, hi);
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    int data[10] = {0};

    default_random_engine e(time(0));
    uniform_int_distribution<int> u(0, 100);

    for (auto &ele : data)
        ele = u(e);

    cout << "before" << endl;
    for (auto ele : data)
    {
        cout << ele << endl;
    }

    QuickSort qs(data, 9);
    qs.qc(data, 9);

    // For test
    int t = 5 >>  1;
    cout << "5 >> 1: " << t << endl;
    cout << "after" << endl;
    for (auto ele : data)
    {
        cout << ele << endl;
    }

    return 0;
}

