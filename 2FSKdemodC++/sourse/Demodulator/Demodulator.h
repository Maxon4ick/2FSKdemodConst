#ifndef DEMOD_H
#define DEMOD_H
#include <cmath>
#include <vector>
#include "../Pll/Pll.h"
class Demodulate
{
public:
virtual std::vector<float> Demod(std::vector<float> &input,float &fs,float &ubd,float &wLo,float &wHi) = 0;

};
class DemodulatorFSK : public Demodulate
{
public:
std::vector<float> Demod(std::vector<float> &input,float &fs,float &ubd,float &wLo,float &wHi) override;

};

std::vector<float> xcorrAbs(std::vector<float> &signal, std::vector<float> &opor);

std::vector<float> genStrob(const std::vector<float> &in, const size_t N, const int nach);

float solution(const std::vector<float> &corOut0,const std::vector<float> &corOut1);
#endif // DEMOD_H
