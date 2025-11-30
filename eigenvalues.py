import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_eigenvalues(filename='eigenvalues_results.csv'):
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
    plt.plot(df['Size'], df['SelfAdjoint_Time(ms)'],
             marker='o', linestyle='-', linewidth=2, label='Self-Adjoint EigenSolver')
    plt.plot(df['Size'], df['General_Time(ms)'],
             marker='s', linestyle='--', linewidth=2, label='General EigenSolver')

    plt.title('Eigenvalue Computation Performance')
    plt.xlabel('Matrix Size (N)')
    plt.ylabel('Time (ms)')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.legend()
    plt.xscale('log')
    plt.yscale('log')
    plt.savefig('eigen_time.png', dpi=300)
    print("Saved as 'eigen_time.png'")
    plt.show()

    # Plot 2: GFLOPS vs Size 
    gflops_general = []
    gflops_selfadj = []
    for i, n in enumerate(df['Size']):
        t_gen_sec = df['General_Time(ms)'][i] / 1000.0
        t_self_sec = df['SelfAdjoint_Time(ms)'][i] / 1000.0

        flops_gen = 20 * n**3        # rough estimation for general
        flops_self = 4.5 * n**3      # rough estimation for self-adjoint

        gflops_general.append(flops_gen / t_gen_sec / 1e9)
        gflops_selfadj.append(flops_self / t_self_sec / 1e9)

    plt.figure(figsize=(10, 6))
    plt.plot(df['Size'], gflops_selfadj,
             marker='o', linestyle='-', linewidth=2, label='Self-Adjoint GFLOPS')
    plt.plot(df['Size'], gflops_general,
             marker='s', linestyle='--', linewidth=2, label='General GFLOPS')

    plt.title('Eigenvalue Computation Performance in GFLOPS')
    plt.xlabel('Matrix Size (N)')
    plt.ylabel('GFLOPS')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.legend()
    plt.xscale('log')
    plt.savefig('eigen_gflops.png', dpi=300)
    print("Saved as 'eigen_gflops.png'")
    plt.show()


if __name__ == "__main__":
    file_path = sys.argv[1] if len(sys.argv) > 1 else 'eigenvalues_results.csv'
    plot_eigenvalues(file_path)
