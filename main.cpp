#include <iostream>
#include <iomanip>
#include <fstream>
#include "lms.h"

/**
 * Simulates LMS filtering with uniformly distributed noise
 */
void uniform_noise_sim(const std::vector<double>& reference, uint32_t n_samples) {
    // Initialize random number generator
    Xorshift32 rng(getpid());
    
    std::vector<double> noise(n_samples);
    std::vector<double> noisy_signal(n_samples);
    std::vector<double> noise_reference(n_samples);
    std::vector<double> error_history(n_samples, 0);
    
    // Generate uniform noise and create noisy signal
    for (size_t i = 0; i < n_samples; i++) {
        // Uniform noise in range [-0.5, 0.5]
        noise[i] = rng.next_double() - 0.5;
        
        // Create correlated noise reference (80% original noise + 20% new noise)
        noise_reference[i] = 0.8 * noise[i] + 0.2 * (rng.next_double() - 0.5);
        
        // Add noise to clean signal
        noisy_signal[i] = reference[i] + noise[i];
    }
    
    std::cout << "FOR UNIFORMLY DISTRIBUTED NOISE\n";
    std::cout << std::fixed << std::setprecision(6);
    
    // Calculate initial error before filtering
    double initial_error = mean_squared_error(noisy_signal, reference);
    std::cout << "Average error in noisy signal:   " << initial_error << std::endl;
    
    // Apply LMS adaptive filter
    std::vector<double> cleaned_signal = lms_filter(noisy_signal, noise_reference, error_history);
    
    // Save error history to file for plotting
    std::ofstream file("error_uniform.txt");
    for (size_t i = 0; i < error_history.size(); i++) {
        file << i << " " << error_history[i] << "\n";
    }
    file.close();
    
    // Calculate final error after filtering
    double final_error = mean_squared_error(cleaned_signal, reference);
    std::cout << "Average error in cleaned signal: " << final_error << std::endl;
    
    // Display noise reduction percentage
    double improvement = (initial_error - final_error) / initial_error * 100;
    std::cout << "Noise reduction: " << improvement << "%" << std::endl;
}

/**
 * Simulates LMS filtering with Gaussian (normal) distributed noise
 */
void awgn_sim(const std::vector<double>& reference, uint32_t n_samples) {
    // Initialize Gaussian random number generator (mean=0, var=0.083)
    nd_rng rng(0, 0.08333333);
    
    std::vector<double> noise(n_samples);
    std::vector<double> noisy_signal(n_samples);
    std::vector<double> noise_reference(n_samples);
    std::vector<double> error_history(n_samples, 0);
    
    // Generate Gaussian noise and create noisy signal
    for (size_t i = 0; i < n_samples; i++) {
        // Gaussian noise with zero mean
        noise[i] = rng.next();
        
        // Create correlated noise reference (80% original noise + 20% new noise)
        noise_reference[i] = 0.8 * noise[i] + 0.2 * rng.next();
        
        // Add noise to clean signal
        noisy_signal[i] = reference[i] + noise[i];
    }
    
    std::cout << "FOR NORMALLY DISTRIBUTED NOISE\n";
    std::cout << std::fixed << std::setprecision(6);
    
    // Calculate initial error before filtering
    double initial_error = mean_squared_error(noisy_signal, reference);
    std::cout << "Average error in noisy signal:   " << initial_error << std::endl;
    
    // Apply LMS adaptive filter
    std::vector<double> cleaned_signal = lms_filter(noisy_signal, noise_reference, error_history);
    
    // Save error history to file for plotting
    std::ofstream file("error_gaussian.txt");
    for (size_t i = 0; i < error_history.size(); i++) {
        file << i << " " << error_history[i] << "\n";
    }
    file.close();
    
    // Calculate final error after filtering
    double final_error = mean_squared_error(cleaned_signal, reference);
    std::cout << "Average error in cleaned signal: " << final_error << std::endl;
    
    // Display noise reduction percentage
    double improvement = (initial_error - final_error) / initial_error * 100;
    std::cout << "Noise reduction: " << improvement << "%" << std::endl;
}

/**
 * Main function: Demonstrates LMS adaptive filtering on noisy sine wave
 * Tests both uniform and Gaussian noise distributions
 */
int main(void) {
    // 1 million samples
    const uint32_t n_samples = 1000000;
    
    // Generate clean sine wave reference signal
    // Angular frequency: π/32 radians per sample
    std::vector<double> reference(n_samples);
    for (size_t i = 0; i < n_samples; i++) {
        double angle = i * (M_PI / 32.0);
        reference[i] = std::sin(angle);
    }
    
    // Test 1: Uniform noise distribution
    uniform_noise_sim(reference, n_samples);
    
    std::cout << "\n*********************************************************************\n\n";
    
    // Test 2: Gaussian noise distribution (AWGN)
    awgn_sim(reference, n_samples);
    
    return 0;
}