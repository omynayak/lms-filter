#ifndef LEAST_MEAN_SQUARES
#define LEAST_MEAN_SQUARES

#include <vector>
#include <cmath>
#include "xorshift.h"
#include "nd_rng.h"

std::vector<double> lms_filter(std::vector<double>& input, std::vector<double>& noise, std::vector<double>& error_history);
double mean_squared_error(const std::vector<double>& input, const std::vector<double>& reference);

#endif