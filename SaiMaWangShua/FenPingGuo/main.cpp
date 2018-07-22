#include <iostream>
#include <cmath>

/**
 * 参考： https://blog.csdn.net/sinat_27339001/article/details/79870541
 */

using namespace std;

int getApples(int N)
{
    return pow(N, N) - N + 1;
}



int main() {
    //std::cout << "Hello, World!" << std::endl;
    int n;
    cin >> n;
    cout << getApples(n) << endl;



    return 0;
}
