import matplotlib.pyplot as plt
import numpy as np

sizes = np.array([32, 64, 128, 256, 512, 1024])
times = np.array([1.37982, 13.0029, 60.9789, 345.373, 2085.81, 15192])

plt.figure(figsize=(8, 6))

plt.plot(sizes, times, marker='o', linewidth=2, label="Householder QR")


plt.xscale('log', base=2)   
plt.yscale('log', base=10)


yticks = [1, 10, 100, 1000, 10000]
plt.yticks(yticks, [r"$10^0$", r"$10^1$", r"$10^2$", r"$10^3$", r"$10^4$"])

plt.title("QR Factorization Runtime vs Matrix Size")
plt.xlabel("Matrix Size (N)")
plt.ylabel("Time (ms)")

plt.grid(True, which='both', linestyle='--', alpha=0.6)
plt.legend()

plt.tight_layout()
plt.show()
