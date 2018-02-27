#include <iostream>
#include "stdexcept"
#include "algorithm"

using namespace std;

int getSum(int n)
{
    int sumT = 0;
    while(n > 0)
    {
        sumT += n % 10;
        n = n / 10;
    }

    return sumT;
}

bool check(int thresh, int rows, int cols, int row, int col, bool *visited)
{
    if(row >= 0 && row < rows && col >= 0 && col < cols && less<int>()(getSum(row) + getSum(col), thresh) && !visited[row * cols + col])
        return true;
    return false;
}

int MovingCountCore(int thresh, int rows, int cols, int row, int col, bool *visited)
{
    int Count = 0;

    if (check(thresh, rows, cols, row, col, visited))
    {
        visited[row * cols + col] = true;
        Count = 1 + MovingCountCore(thresh, rows, cols, row - 1, col, visited)
                + MovingCountCore(thresh, rows, cols, row + 1, col, visited)
                + MovingCountCore(thresh, rows, cols, row, col - 1, visited)
                + MovingCountCore(thresh, rows, cols, row, col + 1, visited);
    }

    return Count;
}

int MovingCount( int thresh, int rows, int cols )
{
    int Count = 0;
    if (rows < 1 || cols < 1)
        return Count;

    //if (!check(thresh, n, rows, cols, 0, 0))
        //throw runtime_error("Invalid Inputs.");
    bool *visited = new bool[rows * cols];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
        {
            visited[i * cols + j] = false;
        }

    Count = MovingCountCore(thresh, rows, cols, 0, 0, visited);

    delete [] visited;

    return Count;
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
