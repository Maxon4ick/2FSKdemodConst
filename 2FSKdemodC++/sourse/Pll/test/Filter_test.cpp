#include <gtest/gtest.h>
#include <vector>
#include <fstream>
#include "../Pll.h"
#include "../../FileManager/FileManager.h"
template<typename t>
void EQUAL_VEC ( std::vector<t>&test,  std::vector<t>&ex)
{
    int num = 0;
    for (int i = 0; i< test.size(); i++)
    {
        if (test[i] == ex[i])
        {
            num+=1;
        }
    }
    assert(num == test.size());
}

TEST(PLL, out0)
{
    const std::string fileNameData = "TestPLLin0.txt";
    const std::string fileNameTest = "TestPLLout0.txt";
    std::vector<short> in = FileManager::readBin<short>(fileNameData);
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    std::vector<float> pllin = FileManager::convertSignal(in);
    size_t n = 160;
    std::vector<float> out = SignalProccesing::synch<float>(pllin,n);
    EQUAL_VEC(test,out);
}
TEST(PLL, out1)
{
    const std::string fileNameData = "TestPLLin1.txt";
    const std::string fileNameTest = "TestPLLout1.txt";
    std::vector<short> in = FileManager::readBin<short>(fileNameData);
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    std::vector<float> pllin = FileManager::convertSignal(in);
    size_t n = 160;
    std::vector<float> out = SignalProccesing::synch<float>(pllin,n);
    EQUAL_VEC(test,out);
}
TEST(Generat,GenLow)
{
    size_t n = 160;
    float f0 = 798;
    float fs = 8e3;
    std::vector<float> out = SignalProccesing::genOp(n,fs,f0);
    std::vector<float> test(n);
    for (int i = 0; i<n; i++)
    {
        test[i] = cos(2*pi*f0/fs*i);
    }
    EQUAL_VEC(test,out);
}

TEST(Generat,GenHi)
{
    size_t n = 160;
    float f0 = 1234;
    float fs = 8e3;
    std::vector<float> out = SignalProccesing::genOp(n,fs,f0);
    std::vector<float> test(n);
    for (int i = 0; i<n; i++)
    {
        test[i] = cos(2*pi*f0/fs*i);
    }
    EQUAL_VEC(test,out);
}
