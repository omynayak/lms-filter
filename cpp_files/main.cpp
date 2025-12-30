#include <iostream>
#include <iomanip>
#include <fstream>
#include "../headers/lms.h"
#include <cstdlib>

void moving_average(const std::vector<double>& cleaned_signal, int d){
    std::vector<double> mov_a(cleaned_signal.size(), 0);
    for(size_t i{4}; i < cleaned_signal.size() - 4; i++){
        double term = cleaned_signal[i];
        for(size_t j = 1; j < 5; j++){
            term += cleaned_signal[i - j] + cleaned_signal[i + j];
        }
        mov_a[i] = term / 9.0;
    }
    if(d == 0){
        std::ofstream uniform("./data/ma_uniform.txt");
        for(size_t i{999000}; i < cleaned_signal.size(); i++){
            uniform << i << " " << mov_a[i] << "\n";
        }
        uniform.close();
        return;
    }

    std::ofstream gaussian("./data/ma_gaussian.txt");
    for(size_t i{999000}; i < cleaned_signal.size(); i++){
        gaussian << i << " " << mov_a[i] << "\n";
    }
    gaussian.close();
    
}


/**
 * Simulates LMS filtering with uniformly distributed noise
 */
void uniform_noise_sim(const std::vector<double>& reference, uint32_t n_samples) {
    // Initialize random number generator
    Xorshift32 rng(getpid());
    
    std::vector<double> noisy_signal(n_samples);
    std::vector<double> noise_reference(n_samples);
    std::vector<double> error_history(n_samples, 0);
    
    // Generate uniform noise and create noisy signal
    for (size_t i = 0; i < n_samples; i++) {
        // Uniform noise in range [-0.5, 0.5]
        double noise = rng.next_double() - 0.5;
        
        // Create correlated noise reference (80% original noise + 20% new noise)
        noise_reference[i] = 0.8 * noise + 0.2 * (rng.next_double() - 0.5);
        
        // Add noise to clean signal
        noisy_signal[i] = reference[i] + noise;
    }
    
    std::cout << "FOR UNIFORMLY DISTRIBUTED NOISE\n";
    std::cout << std::fixed << std::setprecision(6);
    
    // Calculate initial error before filtering
    double initial_error = mean_squared_error(noisy_signal, reference);
    std::cout << "Average error in noisy signal:   " << initial_error << std::endl;
    
    // Apply LMS adaptive filter
    std::vector<double> cleaned_signal = lms_filter(noisy_signal, noise_reference, error_history);
    
    // Save error history to file for plotting
    std::ofstream file("./data/error_uniform.txt");
    for (size_t i = 0; i < error_history.size(); i++) {
        file << i << " " << error_history[i] << "\n";
    }
    file.close();

    std::ofstream uniform("./data/uniform.txt");
    for(long i = 999000; i < 1000000; i++){
        uniform << i << " " << noisy_signal[i] << " " << cleaned_signal[i] << "\n"; 
    }
    uniform.close();

    moving_average(cleaned_signal, 0);
    
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
    
    std::vector<double> noisy_signal(n_samples);
    std::vector<double> noise_reference(n_samples);
    std::vector<double> error_history(n_samples, 0);
    
    // Generate Gaussian noise and create noisy signal
    for (size_t i = 0; i < n_samples; i++) {
        // Gaussian noise with zero mean
        double noise = rng.next();
        
        // Create correlated noise reference (80% original noise + 20% new noise)
        noise_reference[i] = 0.8 * noise + 0.2 * rng.next();
        
        // Add noise to clean signal
        noisy_signal[i] = reference[i] + noise;
    }
    
    std::cout << "FOR NORMALLY DISTRIBUTED NOISE\n";
    std::cout << std::fixed << std::setprecision(6);
    
    // Calculate initial error before filtering
    double initial_error = mean_squared_error(noisy_signal, reference);
    std::cout << "Average error in noisy signal:   " << initial_error << std::endl;
    
    // Apply LMS adaptive filter
    std::vector<double> cleaned_signal = lms_filter(noisy_signal, noise_reference, error_history);
    
    // Save error history to file for plotting
    std::ofstream file("./data/error_gaussian.txt");
    for (size_t i = 0; i < error_history.size(); i++) {
        file << i << " " << error_history[i] << "\n";
    }
    file.close();

    std::ofstream gaussian("./data/gaussian.txt");
    for(int i = 999000; i < 1000000; i++){
        gaussian << i << " " << noisy_signal[i] << " " << cleaned_signal[i] << "\n"; 
    }
    gaussian.close();

    moving_average(cleaned_signal, 1);
    
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
    
    system("python3 ./python_script/plot_convergence.py");
    system("python3 ./python_script/plot_signals.py");
    return 0;
}