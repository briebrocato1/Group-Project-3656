#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <vector>

using Eigen::MatrixXd;

//Measure matrix multiplication 
double measureMatmul(const MatrixXd &A, const MatrixXd &B)
{
    auto start = std::chrono::high_resolution_clock::now();
    MatrixXd C = A * B;
    // Use result so compiler doesn't optimize it away
    volatile double checksum = C(0, 0);
    (void)checksum;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count(); 
}

int main()
{
    std::vector<int> sizes = {32, 64, 128, 256, 512, 1024};
    int repeats = 10; 
    std::cout << "Size,Time_ms,GFLOPS" << std::endl;

    for (int size : sizes)
    {
        MatrixXd A = MatrixXd::Random(size, size);
        MatrixXd B = MatrixXd::Random(size, size);
        measureMatmul(A, B);

        double total_ms = 0.0;
        for (int r = 0; r < repeats; ++r)
        {
            total_ms += measureMatmul(A, B);
        }

        double avg_ms = total_ms / repeats;
        double avg_sec = avg_ms / 1000.0;

        double n = static_cast<double>(size);
        double flops = 2.0 * n * n * n;        // FLOPs per multiplication
        double gflops = flops / avg_sec / 1e9; 

        std::cout << size << "," << avg_ms << "," << gflops << std::endl;
    }

    return 0;
}
