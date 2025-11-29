import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_benchmark(filename='results.csv'):
    if not os.path.exists(filename):
        print(f"Error: '{filename}' not found.")
        return

    try:
        df = pd.read_csv(filename)
    except Exception as e:
        print(f"Error reading CSV: {e}")
        return

    plt.figure(figsize=(10, 6))

    plt.plot(df['Size'], df['Jacobi_Time(ms)'], 
             marker='o', linestyle='-', linewidth=2, label='Jacobi SVD')

    plt.plot(df['Size'], df['BDC_Time(ms)'], 
             marker='s', linestyle='--', linewidth=2, label='BDC SVD')

    plt.title('Eigen SVD Performance: Jacobi vs BDC')
    plt.xlabel('Matrix Size (N)')
    plt.ylabel('Time (ms)')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.legend()

    plt.yscale('log')
    plt.xscale('log')

    output_file = 'svd_benchmark_graph.png'
    plt.savefig(output_file, dpi=300)
    print(f"Graph saved as '{output_file}'")

    # Show the plot
    plt.show()

if __name__ == "__main__":
    # Allow passing filename as argument: python plot_results.py my_data.csv
    file_path = sys.argv[1] if len(sys.argv) > 1 else 'results.csv'
    plot_benchmark(file_path)