#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;


void generateMatrixCycle(int **mat, int columns, int rows, int start, int &idx)
{
    int endX = columns - 1- start;  // column boundary
    int endY = rows - 1 - start;    // row boundary

    // generate a line from left to right
    for(int i = start; i <= endX; ++i)
        mat[start][i] = idx++;

    // generate a line from top to down
    if(start < endY)
        for (int i = start+1; i <= endY; ++i)
            mat[i][endX] = idx++;

    // generate a line from right to left
    if((start < endX) && (start < endY))
        for (int i = endX-1; i >= start; --i)
            mat[endY][i] = idx++;

    // generate a line from down to top
    if((start < endX) && (start < endY - 1))
        for (int i = endY - 1; i >= start + 1; --i)
            mat[i][start] = idx++;
}

void print(int n)
{
    // Complete your code here
    // Numbers must be separated by one space
    if (n == 0)
        return ;

    int rows = sqrt(n+1);
    int cols = rows;

    // determine the input is whether correct or not
    if((rows * rows - 1) != n)
        return ;

    // create a 2D matrix
    int **mat = new int* [rows];
    for (int i = 0; i < rows; ++i)
        mat[i] = new int [cols];

    int start = 0;
    // generate a outer circle every iteration
    int idx = 0;
    while((rows > start * 2) && (cols > start * 2))
    {
        generateMatrixCycle(mat, cols, rows, start, idx);
        ++start;
    }

    // print the 2D matrix
    for(int i = 0; i < rows; ++i)
    {
        int j = 0;
        for(; j < cols - 1; ++j)
            printf("%d ", mat[i][j]);
        printf("%d\n", mat[i][j]);
    }

    // release the dynamic 2D matrix space
    for(int i = 0; i < rows; ++i)
        delete [] mat[i];

    delete [] mat;
}

// ----------------------------
// DO NOT TOUCH THIS CODE BLOCK
#ifndef __NVIDIA_TEST_
// ----------------------------

int main()
{
    // Small test case
    print(24);

    // Large test case
    print(5000 * 5000 - 1);

    // Write your own tests here

    //int i;
    //cin >> i;

    //print(i);
}

// ----------------------------
// DO NOT TOUCH THIS CODE BLOCK
#endif
// ----------------------------
