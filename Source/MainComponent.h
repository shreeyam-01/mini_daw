#pragma once

#include <JuceHeader.h>
#include "Oscillator.h"
#include "uiControl.h"
#include "calculator.h"

class MainComponent  : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    // DSP
    Oscillator oscillator;

    // GUI
    uiControl controls;

 

    std::atomic<float> volume{ 0.2f };
    double currentSampleRate = 44100.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
