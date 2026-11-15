#pragma once
#include "Mode.hpp"
#include <vector>
#include "json.hpp"


class ModeBank{
    private:

        std::vector<Mode> modeBank;
        float sampleRate = 0;
        int numModes = 0;
        void initializeModeBank();

    public:
        
        ModeBank(){
            initializeModeBank();
        }

        const std::vector<Mode>& getModes() {
            return modeBank;
        }

        float getSampleRate(){
            return sampleRate;
        }

        int getNumModes(){
            return numModes;
        }
        
        


};