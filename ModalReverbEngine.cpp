#include "ModalReverbEngine.hpp"
#include "ModeBank.hpp"


ModalReverbEngine::ModalReverbEngine(ModeBank& bank) : modeBank(bank){
    
    audioBuffer.reserve(maxBlockSize);

}


void ModalReverbEngine::prepare(int sampleRate){
    auto numModes = modeBank.getNumModes();
    aReal.resize(numModes);
    aImag.resize(numModes);
    yr.assign(numModes,0.0f);
    yi.assign(numModes,0.0f);
    auto modes = modeBank.getModes();
    for(int i = 0; i < numModes; i++){
        aReal[i] = cos(2*M_PI * modes[i].getFrequency() / sampleRate) * modes[i].getMagnitude();
        aImag[i] = sin(2*M_PI * modes[i].getFrequency() / sampleRate) * modes[i].getMagnitude();
    }
}


void ModalReverbEngine::process(float* inputBuffer, int n, float* outputBuffer){
    float yrTemp = 0;
    float yiTemp = 0;
    float yrPrev = 0;
    float yiPrev = 0;
    for(int i = 0; i < n; i++){
        float sum = 0;
        for(int modeIndex = 0; modeIndex < modeBank.getNumModes(); modeIndex++){
            yrPrev = yr[modeIndex];
            yiPrev = yi[modeIndex];
            yrTemp = inputBuffer[i] * modeBank.getModes()[modeIndex].getGmReal() + aReal[modeIndex] * yrPrev - aImag[modeIndex] * yiPrev;
            yiTemp = inputBuffer[i] * modeBank.getModes()[modeIndex].getGmImag() + aReal[modeIndex] * yiPrev + aImag[modeIndex] * yrPrev;
            sum += yr[modeIndex];
            yr[modeIndex] = yrTemp;
            yi[modeIndex] = yiTemp;
        }
        outputBuffer[i] = sum;       
    }  
}

