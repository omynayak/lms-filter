#ifndef ND_RNG_HPP
#define ND_RNG_HPP

#include <cmath>
#include <cstdint>
#include <unistd.h>

class nd_rng {
private:
    uint32_t state;
    double mean;
    double stddev;

    double uniform() {
        uint32_t x = state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        state = x;

        // strictly (0,1)
        return (x + 1.0) * (1.0 / 4294967297.0);
    }

public:
    nd_rng(double m, double variance)
        : state(getpid()), mean(m), stddev(std::sqrt(variance)) {}

    double next() {
        static bool has_spare = false;
        static double spare;

        if (has_spare) {
            has_spare = false;
            return mean + stddev * spare;
        }

        double u1, u2;
        do {
            u1 = uniform();
            u2 = uniform();
        } while (u1 <= 0.0);

        double r = std::sqrt(-2.0 * std::log(u1));
        double theta = 2.0 * M_PI * u2;

        spare = r * std::sin(theta);
        has_spare = true;

        return mean + stddev * (r * std::cos(theta));
    }
};

#endif
