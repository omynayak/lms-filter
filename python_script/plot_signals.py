import numpy as np
import matplotlib.pyplot as plt

gaussian = np.loadtxt("gaussian.txt")
uniform = np.loadtxt("uniform.txt")


n_g, err_g, cl_g = gaussian[:, 0], gaussian[:, 1], gaussian[:, 2]
n_u, err_u, cl_u = uniform[:, 0],  uniform[:, 1], uniform[:, 2]

plt.figure()
plt.plot(n_u, err_u, label="Noisy Signal")
plt.plot(n_u, cl_u, label="Cleaned Signal")
plt.xlabel("Iteration")
plt.ylabel("Signal value")
plt.title("Clean vs Unclean Sine with Uniform Noise")
plt.legend()
plt.grid(True)

plt.figure()
plt.plot(n_g, err_g, label="Noisy Signal")
plt.plot(n_g, cl_g, label="Cleaned Signal")
plt.xlabel("Iteration")
plt.ylabel("Signal Value")
plt.title("Clean vs Unclean Sine with Gaussian Noise")

plt.legend()
plt.grid(True)

plt.show()
