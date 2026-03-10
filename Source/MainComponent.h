#pragma once

#include <JuceHeader.h>
#include "Oscillator.h"

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
    Oscillator oscillator;
    double currentSampleRate = 44100.0;
    double phase = 0.0;
    double phaseIncrement = 0.0;

    int waveformType = 0;

    juce::Slider frequencySlider; // frequency and volume
    juce::Slider volumeSlider;

    juce::Label frequencyLabel;
    juce::Label volumeLabel;

    // wavefrom selector
    juce::ComboBox waveformSelector;
    juce::Label waveformLabel;

    std::atomic<double> frequency{ 440.0 };
    std::atomic<float> volume{ 0.2f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
