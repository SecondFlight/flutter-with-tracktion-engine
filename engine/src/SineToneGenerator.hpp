#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>

class SineToneGenerator
{
public:
    SineToneGenerator();

    void setFrequency(double frequency);
    void fillNextAudioBuffer(juce::AudioBuffer<float>& buffer);

private:
    double currentFrequency;
    double currentAngle;
    double angleDelta;
    double sampleRate;
};
