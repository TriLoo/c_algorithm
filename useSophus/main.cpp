#include <iostream>
#include "cmath"

using namespace std;

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "sophus/so3.h"
#include "sophus/se3.h"

int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;

    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d(0, 0, 1)).toRotationMatrix();

    // 从旋转矩阵构造李群
    Sophus::SO3 SO3_R(R);
    // 从旋转向量也可以构造李群
    Sophus::SO3 SO3_V(0, 0, M_PI / 2);

    // 或者从四元数构造
    Eigen::Quaterniond q(R);
    Sophus::SO3 SO3_q(q);

    // 输出SO(3)
    cout << "SO(3) from matrix " << SO3_R << endl;
    cout << "SO(3) from vector " << SO3_V << endl;
    cout << "SO(3) from quaternion " << SO3_q << endl;

    // 使用对数映射获得其李代数
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 = " << so3.transpose() << endl;

    // hat 为向量到非对称矩阵
    cout << "so3 hat = " << Sophus::SO3::hat(so3) << endl;
    // vee 为反对称矩阵到向量
    cout << "so3 hat vee = " << Sophus::SO3::vee(Sophus::SO3::hat(so3)).transpose() << endl;

    // 增量扰动模型的更新
    Eigen::Vector3d update_so3(1e-4, 0, 0);
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3) * SO3_R; // 左乘更新
    cout << "SO3 Updated = " << SO3_updated << endl;

    // Test SE3
    Eigen::Vector3d t(1, 0, 0);   // 平移向量
    Sophus::SE3 SE3_Rt(R, t);
    Sophus::SE3 SE3_qt(q, t);
    cout << "SE3 from R, t = " << endl << SE3_Rt << endl;
    cout << "SE3 from q, t = " << endl << SE3_qt << endl;

    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 = " << se3.transpose() << endl;

    // 同样，有hat, vee两个运算符
    cout << "se3 hat = " << endl << Sophus::SE3::hat(se3) << endl;
    cout << "se3 hat vee = " << endl << Sophus::SE3::vee(Sophus::SE3::hat(se3)).transpose() << endl;

    //最后，是更新
    Vector6d updated_se3;
    updated_se3.setZero();

    updated_se3(0, 0) = 1e-4;
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(updated_se3) * SE3_Rt;
    cout << "SE3 Updated = " << endl << SE3_updated.matrix() << endl;


    return 0;
}