#include "PluginProcessor.h"
#include "PluginEditor.h"

SerumLiteAudioProcessor::SerumLiteAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                       .withInput ("Input", juce::AudioChannelSet::stereo(), true)
#endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                       ),
#endif
    parameters(*this, nullptr, "PARAMETERS", {
        std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 1.0f, 0.5f)
    })
{
    oscillator.initialise([](float x) { return std::sin(x); });
}

SerumLiteAudioProcessor::~SerumLiteAudioProcessor() {}

void SerumLiteAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    oscillator.prepare(spec);
    gain.prepare(spec);
    gain.setGainLinear(*parameters.getRawParameterValue("gain"));
}

void SerumLiteAudioProcessor::releaseResources() {}

void SerumLiteAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    juce::dsp::AudioBlock<float> block(buffer);
    oscillator.process(juce::dsp::ProcessContextReplacing<float>(block));
    gain.setGainLinear(*parameters.getRawParameterValue("gain"));
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

juce::AudioProcessorEditor* SerumLiteAudioProcessor::createEditor() { return new SerumLiteAudioProcessorEditor(*this); }
bool SerumLiteAudioProcessor::hasEditor() const { return true; }

const juce::String SerumLiteAudioProcessor::getName() const { return JucePlugin_Name; }
bool SerumLiteAudioProcessor::acceptsMidi() const { return true; }
bool SerumLiteAudioProcessor::producesMidi() const { return false; }
bool SerumLiteAudioProcessor::isMidiEffect() const { return false; }
double SerumLiteAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int SerumLiteAudioProcessor::getNumPrograms() { return 1; }
int SerumLiteAudioProcessor::getCurrentProgram() { return 0; }
void SerumLiteAudioProcessor::setCurrentProgram (int index) {}
const juce::String SerumLiteAudioProcessor::getProgramName (int index) { return {}; }
void SerumLiteAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

void SerumLiteAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SerumLiteAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}
