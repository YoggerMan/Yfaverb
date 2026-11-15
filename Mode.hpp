#pragma once

class Mode{
    private:
        float frequency;
        float magnitude;
        float gmReal;
        float gmImag;

    public:

        Mode(){
            frequency = 0;
            magnitude = 0;
            gmReal = 0;
            gmImag = 0;
        }

        Mode(float freq, float mag, float gmRe, float gmIm)
            : frequency(freq), magnitude(mag), gmReal(gmRe), gmImag(gmIm) {}
        
        float getFrequency() const {
            return frequency;
        }
        float getMagnitude() const {
            return magnitude;
        }
        float getGmReal() const {
            return gmReal;
        }
        float getGmImag() const {
            return gmImag;
        }

    };
