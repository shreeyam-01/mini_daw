#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(600, 400);

    // sterio input
    setAudioChannels(0, 2);
    addAndMakeVisible(controls);


    // connecting slider with sound
    controls.frequencySlider.onValueChange = [this]() {
        double freq = controls.frequencySlider.getValue();
        oscillator.setFrequency(freq);  

        DBG("Frequency (Hz): " + juce::String(freq));
    };

    controls.volumeSlider.onValueChange = [this]() {
        float val = (float)controls.volumeSlider.getValue();
        volume.store(val);
        
        DBG("Volume: " + juce::String(val));
    };

    controls.waveformSelector.onChange = [this]() {
        int type = controls.waveformSelector.getSelectedId() - 1;
        oscillator.setWaveform(type);

        DBG("Waveform type: " + juce::String(type));
     };
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;


    oscillator.setSampleRate(sampleRate);
    oscillator.setFrequency(controls.frequencySlider.getValue());
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();
    auto* left = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* right = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

    float currentVol = volume.load();

    for (int i = 0; i < bufferToFill.numSamples; ++i) {
        float sample = oscillator.getNextSample();

        sample *= currentVol;

        left[i] = sample;
        right[i] = sample;
    }
}

void MainComponent::releaseResources()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    controls.setBounds(getLocalBounds());
}
