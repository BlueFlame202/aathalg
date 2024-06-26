
#include<vector>
#include <random>

namespace algae
{

#ifdef FIXED_SEED
std::default_random_engine generator(42);
#else
std::default_random_engine generator();
#endif

std::normal_distribution<double> normal_dist(0.0,1.0);

double generate_white_noise()
{
    return normal_dist(generator);
}

// Euler-Maruyama scheme for time-homogeneous SDEs
// dXt = b(Xt) dt + sigma(Xt) dBt
std::vector<double> euler_maruyama(double x0, double dt, size_t n, std::function<double(double)> b, std::function<double(double)> sigma, std::function<double()> noise_generator=generate_white_noise)
{
    std::vector<double> res(n);
    res[0] = x0;
    double rdt = sqrt(dt);

    for (int i = 0; i+1 < n; i++)
        res[i+1] = res[i] + b(res[i]) * dt + sigma(res[i]) * rdt * noise_generator();
    return res;
}


}