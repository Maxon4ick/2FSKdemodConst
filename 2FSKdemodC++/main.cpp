#include "sourse/Demodulator/Demodulator.h"
#include "sourse/FileManager/FileManager.h"
#include <string>


int main()
{
    const std::string fileName = "FSK2_8000_50Bd_7_5st5.wav";
    float fs = 8e3;
    float ubd = 50;
    float wLo = 789;
    float wHi = 1234;
    std::vector<short> inRaw = FileManager::readWav<short>(fileName);
    std::vector<float> in = FileManager::convertSignal(inRaw);
    Demodulate *p = new DemodulatorFSK;
    std::vector<float> out = p->Demod(in,fs,ubd,wLo,wHi);
    FileManager::saveSignal(out,"out.bin");
    return 0;
}
