import numpy as np
import matplotlib.pyplot as plt

gaussian = np.loadtxt("error_gaussian.txt")
uniform = np.loadtxt("error_uniform.txt")


n_g, err_g = gaussian[:, 0], gaussian[:, 1]
n_u, err_u = uniform[:, 0],  uniform[:, 1]

plt.figure()
plt.semilogy(n_u, err_u, label="Uniform Noise")
plt.xlabel("Iteration")
plt.ylabel("Mean Squared Error")
plt.title("LMS Convergence: Uniform Noise")
plt.legend()
plt.grid(True)

plt.figure()
plt.semilogy(n_g, err_g, label="Gaussian Noise")
plt.xlabel("Iteration")
plt.ylabel("Mean Squared Error")
plt.title("LMS Convergence: Gaussian Noise")

plt.legend()
plt.grid(True)

plt.show()
