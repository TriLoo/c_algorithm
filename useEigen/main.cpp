#include <iostream>
#include <ctime>

using namespace std;

#include "Eigen/Core"
#include "Eigen/Dense"

#define MATRIX_SIZE 50

// This file test the usage of eigen

int main() {
    std::cout << "Hello, World!" << std::endl;

    Eigen::Matrix<float, 2, 3> matrix_23;

    // typedef Matrix<double, 3, 1> Vector3d;
    Eigen::Vector3d v_3d;
    // typedef Matrix<double, 3, 3> Matrix3d
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();

    // dynamic size matrix
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;

    Eigen::MatrixXd matrix_x;


    // some operations on matrix
    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout << matrix_23 << endl;

    // access matrix element using ()
    for(int i = 0; i < 1; i++)
        for(int j = 0; j < 2; j++)
            cout << matrix_23(i, j) << endl;

    v_3d << 3, 2, 1;

    // before do any operatio, must be sure the type is identical
    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;

    matrix_33 = Eigen::Matrix3d::Random();
    cout << matrix_33 << endl;

    cout << matrix_33.transpose() << endl;
    cout << matrix_33.sum() << endl;
    cout << matrix_33.trace() << endl;
    cout << 10 * matrix_33 << endl;
    cout << matrix_33.inverse() << endl;
    cout << matrix_33.determinant() << endl;

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen Values = " << eigen_solver.eigenvalues() << endl;
    cout << "Eigen Vectors = " << eigen_solver.eigenvectors() << endl;

    // solver the functions
    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t start;
    start = clock();

    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "Time used in normal inverse is  " << 1000.0 * (clock() - start) / (double)CLOCKS_PER_SEC << " ms" << endl;

    // use QR decomposing
    start = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);

    cout << "Time used in Qr composition is " << 1000.0 * (clock() - start) / (double)CLOCKS_PER_SEC << " ms" << endl;



    return 0;
}