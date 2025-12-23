#include <iostream>
#include <iomanip>
#include "lms.h"

Xorshift32 rng(getpid());

int main(void){
    uint32_t n_samples = 1000000;
    
    std::vector<double> reference(n_samples);
    for(size_t i = 0; i < n_samples; i++){
        double angle = M_PI_4 * i * 0.125;
        reference[i] = std::sin(angle);
    }
    
    std::vector<double> noise(n_samples);
    std::vector<double> noisy_signal(n_samples);
    std::vector<double> noise_reference(n_samples);
    for(size_t i = 0; i < n_samples; i++){
        noise[i] = rng.next_double() - 0.5;
        noise_reference[i] = 0.8 * noise[i] + 0.2 * rng.next_double();
        noisy_signal[i] = reference[i] + noise[i];
    }
    
    double initial_error = mean_squared_error(noisy_signal, reference);
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Average error in noisy signal:   " << initial_error << std::endl;
    
    std::vector<double> cleaned_signal = lms_filter(noisy_signal, noise_reference);
    
    double final_error = mean_squared_error(cleaned_signal, reference);
    std::cout << "Average error in cleaned signal: " << final_error << std::endl;
    
    double improvement = (initial_error - final_error) / initial_error * 100;
    std::cout << "Noise reduction: " << improvement << "%" << std::endl;
    
    return 0;
}