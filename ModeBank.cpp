#include "ModeBank.hpp"
#include <fstream>
#include <vector>
#include <string>


using namespace std;
using json = nlohmann::json;


void ModeBank::initializeModeBank(){

    std::fstream modesJsonFile;
    modesJsonFile.open("/Users/christossiantsis/Desktop/DSP/Yfaverb/modes.json");
    json modes = json::parse(modesJsonFile);

    sampleRate = modes.value("sampleRate", 0.0f);
    numModes = modes.value("numModes", 0);
    const auto& modeArray = modes.at("modes");
    modeBank.reserve(modeArray.size());
    for (const auto& modeData : modeArray){
        float frequency = modeData["frequency"];
        float magnitude = modeData["magnitude"];
        float gmReal = modeData["gmReal"];
        float gmImag = modeData["gmImag"];
        modeBank.emplace_back(frequency, magnitude, gmReal, gmImag);
    }


}