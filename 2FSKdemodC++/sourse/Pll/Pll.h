#ifndef FILTER_H
#define FILTER_H
#include <cstdlib>
#include <vector>
#include <cmath>

static double pi = acos(-1.0);

namespace SignalProccesing
{
template<typename t>
std::vector<t> synch(const std::vector<t> &in,const size_t N)
{
    float Ks = 1000;
    float Kd = 1;
    float Ko = 1;
    float wp = 2*pi*300;
    float zeta = 0.5;
    float fs = 8e3;
    float T = 1/fs;
    float f0 = 1.5e3;
    float phi = -1.5;
    float df = 600;
    float fg = f0 - df;
    float teta = df/fs;

    float g1 = 2 * (1 - exp(-wp * zeta * T) * cos(wp * sqrt(1 - zeta*zeta)*T));
    float g2 = g1 + exp(-2 * wp * zeta * T) - 1;
    float Ki = g2 / (Ko*Kd);
    float Kp = g1 / (Ko*Kd);

    std::vector<t> p(N,0);
    std::vector<t> v(N,0);
    std::vector<t> e(N,0);
    std::vector<t> y(N,0);

    for (int i = 1; i<N; i++)
    {
        v[i] = Kd * in[i]*cos(2 * pi * fg/fs * i + p[i-1]);

        e[i] = Kp * v[i] + (Ki-Kp) * v[i-1] + e[i-1];

        p[i] = 1/Ks * Ko * e[i-1] + p[i-1];

        y[i] = Ks * sin(2 * pi * fg/fs * i + p[i-1]);

    }
    return y;
}
std::vector<float> genOp(std::size_t size,float fs, float fn)
{
    std::vector<float> out(size);
    for (int i = 0; i<out.size(); i++)
    {
        out[i] = cos(2*pi*fn/fs*i);
    }
    return out;
}
}

#endif // FILTER_H
