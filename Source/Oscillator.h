/*
  ==============================================================================

    Oscillator.h
    Created: 10 Mar 2026 12:36:21am
    Author:  Shreeyam Acharya

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class Oscillator {
    public:
        void setSampleRate(double sr);
        void setFrequency(double freq);
        void setWaveform(int type);

        float getNextSample();

    private:
        double sampleRate = 44100.0;
        double frequency = 440.0;
        double phase = 0.0;
        double phaseIncrement = 0.0;

        int waveformType = 0;
};