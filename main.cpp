#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <random>
#include <algorithm>
#include "ModeBank.hpp"
#include "ModalReverbEngine.hpp"
#include "AudioFile.h"


using namespace std;

int main(int argc, char* argv[]){

    AudioFile<float> inputIR;
    inputIR.load("/Users/christossiantsis/Desktop/DSP/Yfaverb/K217-ir.wav");
    int numInputSamples = inputIR.getNumSamplesPerChannel();
    cout << numInputSamples << '\n';

    std::vector<float> testIr(numInputSamples, 0.0f);
    testIr[0] = 1;

    std::vector<float> outputBuffer(numInputSamples, 0.0f);

    cout << "running";

    ModeBank modeBank;
    ModalReverbEngine engine = ModalReverbEngine(modeBank);
    int samplesRemaining = numInputSamples;
    engine.prepare(44100);
    int i = 0;
    while(i< numInputSamples){
        if(samplesRemaining < 512){
            engine.process(&testIr[i], samplesRemaining, &outputBuffer[i]);
            i += samplesRemaining;
            break;
        }
        engine.process(&testIr[i], 512, &outputBuffer[i]);
        i += 512;
        samplesRemaining -= 512;
    }

    AudioFile<float> outputFile;
    outputFile.setAudioBufferSize(1,numInputSamples);
    outputFile.setNumChannels(1);
    outputFile.setBitDepth(24);
    outputFile.setSampleRate(48000);
    AudioFile<float>::AudioBuffer buffer(1);
    buffer[0] = outputBuffer;
    outputFile.setAudioBuffer(buffer);
    outputFile.save("/Users/christossiantsis/Desktop/DSP/Yfaverb/out.wav"); 
    
    
    for(int i = 0; i < 20; i++){
        cout<< inputIR.samples[0][i] << " " << outputBuffer[i] << '\n';
    }

}
