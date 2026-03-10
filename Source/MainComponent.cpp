#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(600, 400);

    // sterio input
    setAudioChannels(0, 2);

    // create slider and labels
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

    // connecting slider with sound
    frequencySlider.onValueChange = [this]() {
        double freq = frequencySlider.getValue();
        oscillator.setFrequency(freq);
    };

    volumeSlider.onValueChange = [this]() {
        float val = (float)volumeSlider.getValue();
        volume.store(val);
        
        DBG("Volume 2: " + juce::String(val));
    };

    waveformSelector.onChange = [this]() {
        int type = waveformSelector.getSelectedId() - 1;
        oscillator.setWaveform(type);
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
    oscillator.setFrequency(frequencySlider.getValue());
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
    frequencySlider.setBounds(100, 100, 400, 50);
    volumeSlider.setBounds(100, 200, 400, 50);
    waveformSelector.setBounds(100, 300, 200, 50);
}
