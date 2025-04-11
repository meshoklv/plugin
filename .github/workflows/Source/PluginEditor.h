#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SerumLiteAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SerumLiteAudioProcessorEditor (SerumLiteAudioProcessor&);
    ~SerumLiteAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SerumLiteAudioProcessor& audioProcessor;
    juce::Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SerumLiteAudioProcessorEditor)
};
