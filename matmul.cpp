#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <vector>

// Helper to run a benchmark for a single matrix size n
void benchmark_size(int n, int repeats)
{
    using namespace std::chrono;

    // Create random matrices A and B
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd C(n, n);

    // Warm-up (optional, but helps avoid first-run weirdness)
    C.noalias() = A * B;

    // Time the repeated multiplications
    auto start = high_resolution_clock::now();
    for (int i = 0; i < repeats; ++i)
    {
        C.noalias() = A * B;
    }
    auto end = high_resolution_clock::now();

    // Total time in seconds
    double total_seconds =
        duration_cast<duration<double>>(end - start).count();

    // Average time per matmul in seconds and milliseconds
    double avg_seconds = total_seconds / repeats;
    double avg_ms = avg_seconds * 1000.0;

    // For an n x n matmul, ~2 * n^3 floating-point operations
    double flops = 2.0 * n * n * n;

    // GFLOPS = (flops per matmul) / (time per matmul in seconds) / 1e9
    double gflops = flops / avg_seconds / 1e9;

    // Small use of result so compiler can't optimize everything away
    volatile double checksum = C(0, 0);
    (void)checksum;

    // Print as CSV: n,time_ms,gflops
    std::cout << n << "," << avg_ms << "," << gflops << "\n";
}

int main()
{
    // Matrix sizes to test (adjust if your group uses a different set)
    std::vector<int> sizes = {64, 128, 256, 512, 1024, 2048};

    // You can tune repeats: more for small n, fewer for huge n.
    // To keep it simple, just pick one number that runs fast enough.
    int repeats_small = 100; // for n <= 512
    int repeats_large = 20;  // for n > 512

    // CSV header
    std::cout << "n,time_ms,gflops\n";

    for (int n : sizes)
    {
        int repeats = (n <= 512) ? repeats_small : repeats_large;
        benchmark_size(n, repeats);
    }

    return 0;
}
