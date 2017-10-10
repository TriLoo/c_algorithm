#include <iostream>
#include "opencv2/core.hpp"
#include "ceres/ceres.h"
#include "chrono"

using namespace std;
using namespace cv;

class CURVE_FITTING_COST
{
public:
    CURVE_FITTING_COST (double x, double y):_x(x), _y(y){}

    // 残差计算
    template <typename T>
    bool operator()(const T * const abc, T *residual) const
    {
        // y - exp(ax^2 + bx + c)
        residual[0] = T(_y) - ceres::exp(abc[0]*T(_x) * T(_x) + abc[1]*T(_x) + abc[2]);

        return true;
    }
private:
    const double _x, _y;
};

int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;

    double a = 1, b = 2.0, c = 1.0;
    int N = 100;   // 数据点
    double w_sigma = 1.0;

    RNG rng;    // OpenCV中随机数生成器
    double abc[3] = {0};

    vector<double> x_data, y_data;

    cout << "Generating data : " << endl;
    for(int i = 0; i < N; i++)
    {
        double x = i / 100.0;
        x_data.push_back(x);

        y_data.push_back(
                exp(a * x * x + b * x + c)
        );
    }

    // 构建最小二乘问题
    ceres::Problem problem;
    for(int i = 0; i < N; i++)
    {
        // 选择Ceres的自动求导
        problem.AddResidualBlock(new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(new CURVE_FITTING_COST(x_data[i], y_data[i])), nullptr, abc);
    }

    // 配置求解器
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    ceres::Solve(options, &problem, &summary);
    chrono::steady_clock::time_point stop = chrono::steady_clock::now();
    chrono::duration<double> dura = chrono::duration_cast<chrono::duration<double>>(stop - start);
    cout << "Solve time cost : " << dura.count() << " s" << endl;

    cout << summary.BriefReport() << endl;
    cout << "estimated a, b, c = " ;
    for(auto a : abc)
        cout << a << " ";
    cout << endl;

    return 0;
}
