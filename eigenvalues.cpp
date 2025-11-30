#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <chrono>
#include <vector>

using Eigen::MatrixXd;

// Measure symmetric (self-adjoint) eigenvalue solve
double measureSelfAdjoint(const MatrixXd& A)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    Eigen::SelfAdjointEigenSolver<MatrixXd> es(A);
    volatile double dummy = es.eigenvalues()(0); // prevent optimization
    (void)dummy;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

// Measure general eigenvalue solve
double measureGeneral(const MatrixXd& A)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    Eigen::EigenSolver<MatrixXd> es(A);
    volatile double dummy = es.eigenvalues()(0).real();
    (void)dummy;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

int main()
{
    std::vector<int> sizes = {32, 64, 128, 256, 512, 1024};
    int repeats = 5;

    std::cout << "Size,SelfAdjoint_Time(ms),General_Time(ms)\n";

    for (int n : sizes)
    {
        // Create symmetric (self-adjoint) matrix
        MatrixXd A = MatrixXd::Random(n, n);
        MatrixXd SymA = (A + A.transpose()) * 0.5;

        // Warmups
        measureSelfAdjoint(SymA);
        measureGeneral(A);

        double total_self = 0.0;
        double total_gen  = 0.0;

        for (int r = 0; r < repeats; ++r)
        {
            total_self += measureSelfAdjoint(SymA);
            total_gen  += measureGeneral(A);
        }

        double avg_self = total_self / repeats;
        double avg_gen  = total_gen  / repeats;

        std::cout << n << "," << avg_self << "," << avg_gen << "\n";
    }

    return 0;
}
