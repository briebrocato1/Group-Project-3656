
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
#include <Eigen/Dense>

using Eigen::MatrixXd;

// QR Factorization with Household QR
double measureQR(const MatrixXd& A) {
    auto start = chrono::high_resolution_clock::now();

    Eigen::HouseholderQR<MatrixXd> qr(A);
    double dummy = qr.matrixQR()(0, 0);
    (void)dummy;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

int main() {
    vector<int> sizes = { 32, 64, 128, 256, 512, 1024 };
    int loops = 5;

    cout << "Size,QR_Time(ms)" << endl;

    for (int n : sizes) {
        MatrixXd A = MatrixXd::Random(n, n);

        // First run before data collection
        measureQR(A);

        double total = 0.0;
        for (int r = 0; r < loops; ++r) {
            total += measureQR(A);
        }

        double avg = total / loops;
        cout << n << "," << avg << endl;
    }

    return 0;
}
