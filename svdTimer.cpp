#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <vector>
#include <random>


using Eigen::MatrixXd;

double measureSVD(const MatrixXd& matrix, bool use_bdc) {
    auto start = std::chrono::high_resolution_clock::now();

    if (use_bdc) {
        Eigen::BDCSVD<MatrixXd, Eigen::ComputeThinU | Eigen::ComputeThinV> svd(matrix);
        double dummy = svd.singularValues().coeff(0); //dummy accessor to make sure compiler doesn't optimize calculation away.
    } else {
        Eigen::JacobiSVD<MatrixXd, Eigen::ComputeThinU | Eigen::ComputeThinV> svd(matrix);
        double dummy = svd.singularValues().coeff(0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

int main() {
    std::vector<int> sizes = {32, 64, 128, 256, 512, 1024};
    int repeats = 5;

    std::vector<MatrixXd> matrices;
    for (int size : sizes) {
        matrices.push_back(MatrixXd::Random(size, size));
    }

    std::cout << "Size,Jacobi_Time(ms),BDC_Time(ms)" << std::endl;

    for (size_t i = 0; i < sizes.size(); ++i) {
        double total_jacobi = 0;
        double total_bdc = 0;

        // warmup run to make sure no first run slowdowns occur in timed data.
        measureSVD(matrices[i], false); 
        measureSVD(matrices[i], true);

        for (int r = 0; r < repeats; ++r) {
            total_jacobi += measureSVD(matrices[i], false);
            total_bdc    += measureSVD(matrices[i], true);
        }

        double avg_jacobi = total_jacobi / repeats;
        double avg_bdc = total_bdc / repeats;

        std::cout << sizes[i] << "," << avg_jacobi << "," << avg_bdc << std::endl;
    }

    return 0;
}