/*
  ==============================================================================

    uiControl.h
    Created: 11 Mar 2026 7:31:06pm
    Author:  Shreeyam Acharya

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class uiControl : public juce::Component {
    public:
        uiControl();

        void resized() override;

        juce::Slider frequencySlider;
        juce::Slider volumeSlider;

        juce::ComboBox waveformSelector;

    private:
        juce::Label frequencyLabel;
        juce::Label volumeLabel;
        juce::Label waveformLabel;
    

};