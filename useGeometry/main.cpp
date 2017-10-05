#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

int main() {
    std::cout << "Hello, World!" << std::endl;

    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();

    // use rotate vector
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1));

    cout.precision(3);

    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;


    rotation_matrix = rotation_vector.toRotationMatrix();

    Eigen::Vector3d v(1, 0, 0);

    Eigen::Vector3d rotated_vector = rotation_vector * v;
    cout << "(1, 0, 0) after rotation = " << rotated_vector.transpose() << endl;

    rotated_vector = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation = " << rotated_vector.transpose() << endl;

    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Eigen::Vector3d(1, 3, 4));

    cout << "Transform matrix = \n" << T.matrix() << endl;

    Eigen::Vector3d v_transformed = T * v;
    cout << "v transformed " << v_transformed.transpose() << endl;


    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    cout << "Quaternion = \n" << q.coeffs() << endl;

    q = Eigen::Quaterniond(rotation_matrix);
    cout << "Quaternion = \n" << q.coeffs() << endl;

    rotated_vector = q * v;
    cout << "(1, 0, 0) after rotation = " << rotated_vector.transpose() << endl;

    return 0;
}