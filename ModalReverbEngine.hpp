#pragma once

#include "ModeBank.hpp"
#include <vector>
#include <complex>



class ModalReverbEngine{

    private:
        ModeBank modeBank;
        int maxBlockSize = 512;
        std::vector<float> audioBuffer;
        std::vector<std::complex<float>> y;
        std::vector<float> aReal;
        std::vector<float> aImag;
        std::vector<float> yr;
        std::vector<float> yi;


    public:
    ModalReverbEngine(ModeBank& bank);
    void prepare(int sampleRate);
    void process(float * inputBuffer, int n, float* outputBuffer);
    void filter(float sample, int i);

};

