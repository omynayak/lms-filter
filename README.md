# Adaptive Least-Mean-Squares Filter
A simulation of the Adaptive Least-Mean-Squares filter in C++, complete with zero mean Additive White Gaussian Noise and Uniformly distributed noise and pre and post filtration analysis by plotting the mean squared error convergence, followed by a moving average filter applied to the LMS filtered signal.

## Features:
- Custom zero mean uniform RNG to generate uniformly distributed noise.
- Custom AWGN generation using the Box-Muller transform.
- From-scratch implementation of a 32-order Least-Mean-Squares filter with adaptive step size based on power of the signal.
- Custom function to evaluate the mean squared error of a signal given the reference.
- Tracks and stores error history to later plot mean squared error convergence.
- Uses moving average filter of kernel size 9 to smoothen out the result
- Plots the noisy signal, lms-cleaned signal, and lms + moving average cleaned signal of both uniform noise and awgn using matplotlib.
- Also plots mean squared error convergence using matplotlib.

## Project Structure:
```
.
├── cpp_files
    ├── lms.cpp
    └── main.cpp
├── headers
    ├── lms.h
    ├── nd_rng.h
    └── xorshift.h
├── python_script
    ├── plot_convergence.py
    └── plot_signals.py
├── Makefile
└── README.md
```
