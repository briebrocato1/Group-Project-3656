import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_matmul(filename='matmul_results.csv'):
    if not os.path.exists(filename):
        print(f"Error: '{filename}' not found.")
        return

    try:
        df = pd.read_csv(filename, encoding="utf-8-sig")
    except Exception as e:
        print(f"Error reading CSV: {e}")
        return

    # --- Plot 1: Time vs Size ---
    plt.figure(figsize=(10, 6))
    plt.plot(df['Size'], df['Time_ms'],
             marker='o', linestyle='-', linewidth=2, label='Matmul Time')

    plt.title('Eigen Matmul Performance: Time vs Matrix Size')
    plt.xlabel('Matrix Size (N)')
    plt.ylabel('Time (ms)')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.savefig('matmul_time.png', dpi=300)
    print("Saved 'matmul_time.png'")
    plt.show()

    # --- Plot 2: GFLOPS vs Size ---
    plt.figure(figsize=(10, 6))
    plt.plot(df['Size'], df['GFLOPS'],
             marker='s', linestyle='--', linewidth=2, label='Matmul GFLOPS')

    plt.title('Eigen Matmul Performance: GFLOPS vs Matrix Size')
    plt.xlabel('Matrix Size (N)')
    plt.ylabel('GFLOPS')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.xscale('log')

    plt.legend()
    plt.savefig('matmul_gflops.png', dpi=300)
    print("Saved 'matmul_gflops.png'")
    plt.show()

if __name__ == "__main__":
    file_path = sys.argv[1] if len(sys.argv) > 1 else 'matmul_results.csv'
    plot_matmul(file_path)
