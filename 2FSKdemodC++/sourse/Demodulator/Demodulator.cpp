#include "Demodulator.h"

std::vector<float> DemodulatorFSK:: Demod(std::vector<float> &input,float &fs,float &ubd,float &wLo,float &wHi)
{
    int sampleSize = fs/ubd;
    int outSize = round(input.size()/sampleSize);
    std::vector<float> out(outSize,0);
    std::vector<float> op0 = SignalProccesing::genOp(sampleSize,fs,wLo);
    std::vector<float> op1 = SignalProccesing::genOp(sampleSize,fs,wHi);

    for (int i = 0; i<outSize; i++)
    {
        int sek = i*sampleSize;
        std::vector<float> strob = genStrob(input,sampleSize,sek);
        std::vector<float> syn = SignalProccesing::synch(strob,sampleSize);
        std::vector<float> corOut0 = xcorrAbs(syn,op0);
        std::vector<float> corOut1 = xcorrAbs(syn,op1);
        out[i] = solution(corOut0,corOut1);
    }
    return out;
}
std::vector<float> xcorrAbs(std::vector<float> &signal, std::vector<float> &opor)
{
    int len = signal.size();
    std::vector<float> r(2*len,0);
    for (int delay = -len; delay<len; delay++)
    {
        float sxy = 0;
        for (int i = 0; i<len; i++)
        {
            int j = i + delay;
            if((j < 1) || (j >= len))
            {sxy += 0;}
            else
            {sxy += signal[i] * opor[j];}
        }
        r[delay + len] = sxy;
    }

    for (int i = 0; i<r.size(); i++)
    {
        r[i] = fabs(r[i]);
    }
    return r;
}

std::vector<float> genStrob(const std::vector<float> &in,const size_t N,const int nach)
{
    std::vector<float> strob(N,0);
    for (int i = 0; i<N; i++)
    {
        strob[i] = in[nach+i];

    }
    return strob;
}

float solution(const std::vector<float> &corOut0,const std::vector<float> &corOut1)
{
    float max0 = 0;
    float max1 = 0;
    float sol = 0;
    for (int i = 0; i<corOut0.size(); i++)
    {
        if (corOut0[i]>max0)
        {max0 = corOut0[i];}

        if (corOut1[i]>max1)
        {max1 = corOut1[i];}
    }
    if(max1>max0)
    {
        sol = 1;
    }
    return sol;
}
