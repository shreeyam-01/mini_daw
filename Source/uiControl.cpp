/*
  ==============================================================================

    uiControl.cpp
    Created: 11 Mar 2026 7:31:06pm
    Author:  Shreeyam Acharya

  ==============================================================================
*/

#include "uiControl.h"

uiControl::uiControl() {
    frequencySlider.setRange(50.0, 2000.0);
    frequencySlider.setValue(440.0);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(frequencySlider);

    frequencyLabel.setText("Frequency (Hz)", juce::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, false);
    addAndMakeVisible(frequencyLabel);

    volumeSlider.setRange(0.0, 1.0);
    volumeSlider.setValue(0.6);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(volumeSlider);

    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, false);
    addAndMakeVisible(volumeLabel);

    // constructing waveformSelector
    waveformSelector.addItem("Sine", 1);
    waveformSelector.addItem("Square", 2);
    waveformSelector.addItem("Saw", 3);
    waveformSelector.addItem("Triangle", 4);

    waveformSelector.setSelectedId(1);
    addAndMakeVisible(waveformSelector);

    waveformLabel.setText("Waveform", juce::dontSendNotification);
    waveformLabel.attachToComponent(&waveformSelector, false);
    addAndMakeVisible(waveformLabel);
}

void uiControl::resized() {
    frequencySlider.setBounds(100, 100, 400, 50);
    volumeSlider.setBounds(100, 200, 400, 50);
    waveformSelector.setBounds(100, 300, 200, 50);
}
