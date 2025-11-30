# Group-Project-3656

### SVD Portion
svdTimer.cpp holds the timing calculator for jacobi vs BDC svd solvers. It calculates SVD with randomly populated, increasing size matrices to compare the speed between the different methods.<br>
Compilation Instructions:<br>
This benchmark requires Eigen to be installed to run. Follow instructions on Eigen page, and install it where you'd like. Once eigen is installed, run this command to compile the benchmark. 
```
g++ -I /path/to/eigen -O3 svdTimer.cpp -o svdTimer
```
To run, you must execute the svdTimer and pipe the output to a file results.csv for later examination.
```
./svdTimer > results.csv
```
From here, simploy execute the svdPlotter, and you will see your results.
```
python3 svdPlotter.py
```
As long as the results.csv file exists, your results will be graphed out for comparison. 


### Matmul Portion
matmulTimer.cpp benchmarks the performance of matrix multiplication using Eigen Software. It generates random square matrices of increasing size and measures bthe average computation time and the floating-point throughput(GFLOPS).

Compilation will follow the same structure as the SVD benchmark. Once Eigen is installed locally, compile the matmul benchmark with:
```
g++ -I /path/to/eigen -O3 matmulTimer.cpp -o matmulTimer
```
Run the executable and the output will be put into a CSV file:
```
./matmulTimer > matmul_results.csv
```
To see the timing and GFLOPS results in a graph, run the provided plotting script:
```
python matmulPlotter.py
```
Two plots will be generated: one for runtime/matrix size and one for GFLOPS/matrix size.  As long as matmul_results.csv exists in the project directory.


