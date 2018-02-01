#include <iostream>
#include "vector"
#include "string"
#include "fstream"

#include "Eigen/Core"
#include "sophus/se3.h"
#include "sophus/so3.h"

#include "gtsam/slam/dataset.h"
#include "gtsam/slam/BetweenFactor.h"
#include "gtsam/slam/PriorFactor.h"
#include "gtsam/nonlinear/GaussNewtonOptimizer.h"
#include "gtsam/nonlinear/LevenbergMarquardtOptimizer.h"

using namespace std;
using Sophus::SE3;
using Sophus::SO3;

int main()
{
    std::cout << "Hello, World!" << std::endl;

    // read .g2o file
    ifstream fin("./sphere.g2o");

    gtsam::NonlinearFactorGraph::shared_ptr graph(new gtsam::NonlinearFactorGraph);
    gtsam::Values::shared_ptr initial(new gtsam::Values);

    int cntVertex = 0, cntEdge = 0;
    cout << "Reading from g2o file." << endl;

    while(!fin.eof())
    {
        string name;
        fin >> name;
        if(name == "VERTEX_SE3:QUAT")
        {
            gtsam::Key  id;
            fin >> id;
            double data[7];
            for (int i = 0; i < 7; ++i)
                fin >> data[i];
            gtsam::Rot3 R = gtsam::Rot3::Quaternion(data[6], data[3], data[4], data[5]);
            gtsam::Point3 t(data[0], data[1], data[2]);
            initial->insert(id, gtsam::Pose3(R, t));
            cntVertex++;
        }
        else if(name == "EDGE_SE3:QUAT")
        {
            gtsam::Matrix m = gtsam::I_6x6;
            gtsam::Key id1, id2;
            fin >> id1 >> id2;
            double data[7];

            for (int i = 0; i < 7; ++i)
                fin >> data[i];

            gtsam::Rot3 R = gtsam::Rot3::Quaternion(data[6], data[3], data[4], data[5]);
            gtsam::Point3 t(data[0], data[1], data[2]);

            for (int i = 0; i < 6; ++i)
                for (int j = i; j < 6; ++j)
                {
                    double mij;
                    fin >> mij;
                    m(i, j) = mij;
                    m(j, i) = mij;
                }

            gtsam::Matrix mgtsam = gtsam::I_6x6;
            mgtsam.block<3, 3>(0, 0) = m.block<3, 3>(3, 3);
            mgtsam.block<3, 3>(3, 3) = m.block<3, 3>(0, 0);
            mgtsam.block<3, 3>(0, 3) = m.block<3, 3>(0, 3);
            mgtsam.block<3, 3>(3, 0) = m.block<3, 3>(3, 0);

            gtsam::SharedNoiseModel model = gtsam::noiseModel::Gaussian::Information(mgtsam);
            gtsam::NonlinearFactor::shared_ptr factor(new gtsam::BetweenFactor<gtsam::Pose3>(id1, id2, gtsam::Pose3(R, t), model));
            graph->push_back(factor);
            cntEdge++;
        }
        if (!fin.good())
            break;
    }

    cout << "Read total " << cntVertex << "vertices, " << cntEdge << " edges." << endl;

    gtsam::NonlinearFactorGraph graphWithPrior = *graph;
    gtsam::noiseModel::Diagonal::shared_ptr priorModel = gtsam::noiseModel::Diagonal::Variances((gtsam::Vector(6) << 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6).finished());
    gtsam::Key  firstKey = 0;

    for (const gtsam::Values::ConstKeyValuePair& key_value : *initial)
    {
        cout << "Adding prior to g2o file." << endl;
        graphWithPrior.add(gtsam::PriorFactor<gtsam::Pose3>(key_value.key, key_value.value.cast<gtsam::Pose3>(), priorModel));
        break;
    }

    // begin optimization
    cout << "Begin the Optimization." << endl;
    gtsam::LevenbergMarquardtParams params_lm;
    params_lm.setVerbosity("ERROR");
    params_lm.setMaxIterations(20);
    params_lm.setLinearSolverType("MULTIFRONTAL_QR");

    gtsam::LevenbergMarquardtOptimizer optimizer_LM(graphWithPrior, *initial, params_lm);

    gtsam::Values result = optimizer_LM.optimize();

    ofstream fout("result_gtsam.g2o");

    for (const gtsam::Values::ConstKeyValuePair& key_value : result)
    {
        gtsam::Pose3 pose = key_value.value.cast<gtsam::Pose3>();
        gtsam::Point3 p = pose.translation();
        gtsam::Quaternion q = pose.rotation().toQuaternion();
        fout << "VERTEX_SE3:QUAT " << key_value.key << " " << p.x() << " " << p.y() << " " << p.z() << " "
                                                                                                    << q.x() << " " << q.y() << " " << q.z()
                                                                                                    << " " << q.w() << " " << endl;
    }

    for (const gtsam::NonlinearFactor::shared_ptr factor : * graph)
    {
        gtsam::BetweenFactor<gtsam::Pose3>::shared_ptr f = dynamic_pointer_cast<gtsam::BetweenFactor<gtsam::Pose3>>(factor);

        if (f)
        {
            gtsam::SharedNoiseModel model = f->noiseModel();
            gtsam::noiseModel::Gaussian::shared_ptr gaussianModel = dynamic_pointer_cast<gtsam::noiseModel::Gaussian>(model);
            if (gaussianModel)
            {
                gtsam::Matrix info = gaussianModel->R().transpose() * gaussianModel->R();
                gtsam::Pose3 pose = f->measured();
                gtsam::Point3 p = pose.translation();

                gtsam::Quaternion q = pose.rotation().toQuaternion();
                fout << "EDGE_SE3:QUAT " << f->key1() << " " << f->key2() << " "
                        << p.x() << " " << p.y() << " " << p.z() << " "
                        << q.x() << " " << q.y() << " " << q.z()
                        << " " << q.w() << " " << endl;

                gtsam::Matrix infoG2o = gtsam::I_6x6;
                infoG2o.block(0,0,3,3) = info.block(3,3,3,3); // cov translation
                infoG2o.block(3,3,3,3) = info.block(0,0,3,3); // cov rotation
                infoG2o.block(0,3,3,3) = info.block(0,3,3,3); // off diagonal
                infoG2o.block(3,0,3,3) = info.block(3,0,3,3); // off diagonal
                for ( int i=0; i<6; i++ )
                        for ( int j=i; j<6; j++ )
                        {
                            fout<<infoG2o(i,j)<<" ";
                        }
                fout<<endl;
            }
        }
    }

    return 0;
}
