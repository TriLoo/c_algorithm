#include <iostream>
#include "memory"
#include "cstring"

using namespace std;

#define ROWS 3
#define COLS 4

bool hasPathCore(char *m, int rows, int cols, int row, int col, char *str, int& pathLen, bool* visited)
{
    if (str[pathLen] == '\0')
        return true;

    bool has = false;
    if (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row * cols + col] && m[row * cols + col] == str[pathLen] )
    {
        visited[row * cols + col] = true;
        pathLen++;
        has = hasPathCore(m, rows, cols, row-1 , col, str, pathLen, visited) ||
                hasPathCore(m, rows, cols, row+1, col, str, pathLen, visited) ||
                hasPathCore(m, rows, cols, row, col - 1, str, pathLen, visited) ||
                hasPathCore(m, rows, cols, row, col + 1, str, pathLen, visited);

        if (!has)
        {
            visited[row * cols + col] = false;
            pathLen--;
        }
    }

    return has;
}

bool hasPath(char *m, int rows, int cols, char *str)
{
    if (m == nullptr || rows < 1 || cols < 1 || str == nullptr)
        return false;

    bool *visited = new bool[ROWS * COLS];
    memset(visited, 0, sizeof(bool) * ROWS * COLS);

    int pathLen = 0;
    // The first chooses, total rows * cols element for the first one element
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (hasPathCore(m, rows, cols, i, j, str, pathLen, visited))
                return true;
        }
    }

    delete [] visited;

    return false;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    /*
    //shared_ptr<char> matrix(new char [ROWS * COLS]);
    shared_ptr<char> matrix = make_shared<char>({'a', 'b', 't', 'g',
                                                'c', 'f', 'c', 's',
                                                'j', 'd', 'e', 'h'});
    */

    //cout << "Size of bool: " << endl;
    //cout << sizeof(bool) << endl;             // return: 1

    char matrix[] = {'a', 'b', 't', 'g',
                   'c', 'f', 'c', 's',
                   'j', 'd', 'e', 'h'};

    char strA[] = {'b', 'f', 'c', 'e', '\0'};
    //char *strT = "bfce";            // Work
    //char strT[] = "bfce";           // Work
    //char strT[5] = "bfce";            // Work
    if (hasPath(matrix, ROWS, COLS, strA))
        cout << "There is the path." << endl;
    else
        cout << "There isn't the path." << endl;

    char strB[] = {'a', 'b', 'f', 'b', '\0'};
    if (hasPath(matrix, ROWS, COLS, strB))
        cout << "There is the path." << endl;
    else
        cout << "There isn't the path." << endl;


    return 0;
}
