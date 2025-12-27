#include "../headers/lms.h"

std::vector<double> lms_filter(std::vector<double>& input, std::vector<double>& noise, std::vector<double>& error_history){
    double mu = 0.0025;
    int order = 32;
    std::vector<double> weight_vector(32, 0);
    uint32_t n_samples = input.size();

    std::vector<double> cleaned_signal(n_samples, 0);
    
    for(size_t i = order; i < n_samples; i++){

        double power = 1e-6;
        for(size_t k = 0; k < order; k++){
            power += noise[i - k] * noise[i - k];
        }

        double mu_n = mu / power;
        double predicted_noise = 0;
        for(size_t k = 0; k < order; k++){
            predicted_noise += weight_vector[k] * noise[i - k];
        }

        cleaned_signal[i] = input[i] - predicted_noise;
        error_history[i] = (cleaned_signal[i] * cleaned_signal[i]);

        for (size_t k = 0; k < order; k++) {
            weight_vector[k] += mu_n * cleaned_signal[i] * noise[i - k];
        }
    }

    return cleaned_signal;
}

double mean_squared_error(const std::vector<double>& input, const std::vector<double>& reference){
    double sum = 0;
    uint32_t n_samples = input.size();
    
    for(size_t i = 0; i < n_samples; i++){
        sum += pow(reference[i] - input[i], 2);
    }
    
    return sum / n_samples;
}