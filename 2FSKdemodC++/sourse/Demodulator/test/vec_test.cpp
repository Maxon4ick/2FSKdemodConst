#include <gtest/gtest.h>
#include <vector>
#include <fstream>
#include "../Demodulator.h"
#include <cmath>
#include "../../FileManager/FileManager.h"
#include "../../Pll/Pll.h"


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



TEST(XcorrAbs,corrLowTrue)
{
    size_t n = 160;
    float f0 = 798;
    float fs = 8e3;
    std::vector<float> gen =SignalProccesing::genOp(n,fs,f0);
    const std::string fileNameData = "TestPLLout0.txt";
    const std::string fileNameTest = "TestCorout0True.txt";
    std::vector<float> in = FileManager::readBin<float>(fileNameData);
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    std::vector<float> out = xcorrAbs(in,gen);
    EQUAL_VEC(test,out);
}
TEST(XcorrAbs,corrLowFalse)
{
    size_t n = 160;
    float f0 = 1234;
    float fs = 8e3;
    std::vector<float> gen =SignalProccesing::genOp(n,fs,f0);
    const std::string fileNameData = "TestPLLout0.txt";
    const std::string fileNameTest = "TestCorout0False.txt";
    std::vector<float> in = FileManager::readBin<float>(fileNameData);
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    std::vector<float> out = xcorrAbs(in,gen);
    EQUAL_VEC(test,out);
}
TEST(XcorrAbs,corrHiTrue)
{
    size_t n = 160;
    float f0 = 1234;
    float fs = 8e3;
    std::vector<float> gen =SignalProccesing::genOp(n,fs,f0);
    const std::string fileNameData = "TestPLLout1.txt";
    const std::string fileNameTest = "TestCorout1True.txt";
    std::vector<float> in = FileManager::readBin<float>(fileNameData);
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    std::vector<float> out = xcorrAbs(in,gen);
    EQUAL_VEC(test,out);
}
TEST(XcorrAbs,corrHiFalse)
{
    size_t n = 160;
    float f0 = 798;
    float fs = 8e3;
    std::vector<float> gen =SignalProccesing::genOp(n,fs,f0);
    const std::string fileNameData = "TestPLLout1.txt";
    const std::string fileNameTest = "TestCorout1False.txt";
    std::vector<float> in = FileManager::readBin<float>(fileNameData);
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    std::vector<float> out = xcorrAbs(in,gen);
    EQUAL_VEC(test,out);
}

TEST(GenStrob,StrobN160S0)
{
    size_t n = 160;
    int nach = 0;
    const std::string fileNameData = "FSK2_8000_50Bd_7_5st5.wav";
    std::vector<short> ex = FileManager::readWav<short>(fileNameData);
    std::vector<float> in  = FileManager::convertSignal(ex);
    std::vector<float> strob = genStrob(in,n,nach);
    const std::string fileNameTest = "TestStrobOut0.txt";
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    EQUAL_VEC(test,strob);
}

TEST(GenStrob,StrobN160S160)
{
    size_t n = 160;
    int nach = 160;
    const std::string fileNameData = "FSK2_8000_50Bd_7_5st5.wav";
    std::vector<short> ex = FileManager::readWav<short>(fileNameData);
    std::vector<float> in  = FileManager::convertSignal(ex);
    std::vector<float> strob = genStrob(in,n,nach);
    const std::string fileNameTest = "TestStrobOut160.txt";
    std::vector<float> test = FileManager::readBin<float>(fileNameTest);
    EQUAL_VEC(test,strob);
}

TEST(SolTest, Sol0)
{
    const std::string fileNameData0 = "TestSolIn0True.txt";
    const std::string fileNameData1 = "TestSolIn1False.txt";
    std::vector<float> corOut0 = FileManager::readBin<float>(fileNameData0);
    std::vector<float> corOut1 = FileManager::readBin<float>(fileNameData1);
    float ex = solution(corOut0,corOut1);
    float test = 0;
    EXPECT_DOUBLE_EQ(ex,test);
}
TEST(SolTest, Sol1)
{
    const std::string fileNameData0 = "TestSolIn0False.txt";
    const std::string fileNameData1 = "TestSolIn1True.txt";
    std::vector<float> corOut0 = FileManager::readBin<float>(fileNameData0);
    std::vector<float> corOut1 = FileManager::readBin<float>(fileNameData1);
    float ex = solution(corOut0,corOut1);
    float test = 1;
    EXPECT_DOUBLE_EQ(ex,test);
}
TEST(DemodTest, FIN)
{
    const std::string fileName = "TestWavOut.txt";
    float fs = 8e3;
    float ubd = 50;
    float wLo = 789;
    float wHi = 1234;
    std::vector<float> test = {0, 1, 1};
    std::vector<float> in = FileManager::readBin<float>(fileName);
    Demodulate *p = new DemodulatorFSK;
    std::vector<float> out = p->Demod(in,fs,ubd,wLo,wHi);
    EQUAL_VEC(test,out);
}
