#include "PluginProcessor.h"
#include "PluginEditor.h"

SerumLiteAudioProcessorEditor::SerumLiteAudioProcessorEditor (SerumLiteAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setRange(0.0f, 1.0f, 0.01f);
    gainSlider.setValue(0.5f);
    gainSlider.onValueChange = [this] {
        *audioProcessor.parameters.getRawParameterValue("gain") = gainSlider.getValue();
    };
    addAndMakeVisible(gainSlider);
    setSize (400, 150);
}

void SerumLiteAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Serum Lite", getLocalBounds(), juce::Justification::centred, 1);
}

void SerumLiteAudioProcessorEditor::resized()
{
    gainSlider.setBounds(10, 100, getWidth() - 20, 20);
}
