import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_qr(filename='qr_results.csv'):
    if not os.path.exists(filename):
        print(f"Error: '{filename}' not found.")
        return

    try:
        df = pd.read_csv(filename, encoding="utf-8-sig")
    except Exception as e:
        print(f"Error reading CSV: {e}")
        return

    if 'Size' not in df.columns or 'QR_Time(ms)' not in df.columns:
        print("CSV must have columns: 'Size' and 'QR_Time(ms)'")
        print("First line of the file should look like: Size,QR_Time(ms)")
        return


    plt.figure(figsize=(10, 6))
    plt.plot(
        df['Size'],
        df['QR_Time(ms)'],
        marker='o',
        linestyle='-',
        linewidth=2,
        label='QR Time'
    )

    plt.title('Eigen QR Performance: Time vs Matrix Size')
    plt.xlabel('Matrix Size (N)')
    plt.ylabel('Time (ms)')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)

    plt.xscale('log')
    plt.yscale('log')

    plt.legend()

    output_file = 'qr_time.png'
    plt.savefig(output_file, dpi=300)
    print(f"Saved '{output_file}'")
    plt.show()


if __name__ == "__main__":
    file_path = sys.argv[1] if len(sys.argv) > 1 else 'qr_results.csv'
    plot_qr(file_path)
