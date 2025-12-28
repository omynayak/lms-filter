import numpy as np
import matplotlib.pyplot as plt

gaussian = np.loadtxt("gaussian.txt")
uniform = np.loadtxt("uniform.txt")

n_g, err_g, cl_g = gaussian[:, 0], gaussian[:, 1], gaussian[:, 2]
n_u, err_u, cl_u = uniform[:, 0],  uniform[:, 1], uniform[:, 2]



fig_u, axs_u = plt.subplots(2, 1, sharex=True)

axs_u[0].plot(n_u, err_u)
axs_u[0].set_title("Uniform Noise – Noisy Signal")
axs_u[0].set_ylabel("Signal Value")
axs_u[0].grid(True)

axs_u[1].plot(n_u, cl_u)
axs_u[1].set_title("Uniform Noise – Cleaned Signal")
axs_u[1].set_xlabel("Iteration")
axs_u[1].set_ylabel("Signal Value")
axs_u[1].grid(True)

fig_u.suptitle("Uniform Noise: Noisy vs Cleaned Signal")




fig_g, axs_g = plt.subplots(2, 1, sharex=True)

axs_g[0].plot(n_g, err_g)
axs_g[0].set_title("Gaussian Noise – Noisy Signal")
axs_g[0].set_ylabel("Signal Value")
axs_g[0].grid(True)

axs_g[1].plot(n_g, cl_g)
axs_g[1].set_title("Gaussian Noise – Cleaned Signal")
axs_g[1].set_xlabel("Iteration")
axs_g[1].set_ylabel("Signal Value")
axs_g[1].grid(True)

fig_g.suptitle("Gaussian Noise: Noisy vs Cleaned Signal")

plt.show()
