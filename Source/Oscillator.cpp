/*
  ==============================================================================

    Oscillator.cpp
    Created: 10 Mar 2026 12:36:21am
    Author:  Shreeyam Acharya

  ==============================================================================
*/

#include "Oscillator.h"

void Oscillator::setSampleRate(double sr) {
    sampleRate = sr;
}

void Oscillator::setFrequency(double freq) {
    frequency = freq;

    phaseIncrement = juce::MathConstants<double>::twoPi * frequency / sampleRate;
}

void Oscillator::setWaveform(int type) {
    waveformType = type;
}

float Oscillator::getNextSample() {
    float sample = 0.0f; // sample of sound

    switch (waveformType)
    {
    case 0:
        sample = std::sin(phase);
        break; // sim

    case 1:
        sample = (phase < juce::MathConstants<double>::pi) ? 1.0f : -1.0f;
        break; // square

    case 2:
        sample = (float)(phase / juce::MathConstants<double>::pi - 1.0);
        break; // saw

    case 3:
        sample = std::asin(std::sin(phase)) * (2.0 / juce::MathConstants<double>::pi);
        break;
    }

    

    phase += phaseIncrement;

    if (phase >= juce::MathConstants<double>::twoPi) {
        phase -= juce::MathConstants<double>::twoPi;
    }

    return sample;
}
