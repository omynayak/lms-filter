#ifndef LEAST_MEAN_SQUARES
#define LEAST_MEAN_SQUARES

#include <vector>
#include <cmath>
#include "xorshift.h"

std::vector<double> lms_filter(std::vector<double>& input, std::vector<double>& noise);
double mean_squared_error(const std::vector<double>& input, const std::vector<double>& reference);

#endif