/**
 * @author smh
 * @date 2018.08.04
 *
 * @brief 剑指offer第29题
 *
 * @brief 思路：
 *          1. 整个代码分为两部分：一个函数负责决定循环的终止，也就是每次打印一圈，所有的打印次数；然后另一个函数打印当前循环的那一圈数字
 *          2. 最外层循环的继续条件是： 矩阵的列数 > 2 * 当前一圈开始的左上角的x坐标 && 矩阵的行数 > 2 * 当前一圈开始的左上角的y坐标
 */
#include <iostream>

using namespace std;

void printMatrixCircle(int **mat, int cols, int rows, int start);

/**
 * @brief  使用二阶指针表示二阶矩阵
 *
 * @param mat
 * @param cols
 * @param rows
 */
void printMatrixClockwise(int **mat, int cols, int rows)
{
    int start = 0;

    while ((start * 2 < cols) && (start * 2 < rows))
        printMatrixCircle(mat, cols, rows,  start);
}

/**
 * @brief 打印一圈数字的时候，分成四步完成
 *          1. 从左到右打印一行： 终止的列数大于起始的列数
 *          2. 从上到下打印一列：终止的行数大于起始的行数
 *          3. 从右到左打印一行： 终止的行数大于起始的行号，同时终止的列号也要大于起始的列号
 *          4. 从下到上打印一列： 终止的列号大于起始的列号，同时终止的行号也要大于起始的行两行!
 *
 * @param mat
 * @param startX
 * @param startY
 */
void printMatrixCircle(int **mat, int cols, int rows, int start)
{
    int endX = cols - start - 1;
    int endY = rows - start - 1;

    // 第一步
    for (int i = start; i <= endX; ++i)
        cout << mat[start][i];      // 打印一行
    
    // 第二步
    if (start < endY)
        for (int i = start; i <= endY; ++i)
            cout << mat[i][endX];      // 打印一列

    // 第三步
    if (start < endY && start < endX)
    {
        for (int i = endY; i >= start; --i)
            cout << mat[endY][i];
    }
    
    // 第四步
    if (start < endY - 1 && start < endX)
        for (int i = endY; i >= start; --i)
            cout << mat[i][start];
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
