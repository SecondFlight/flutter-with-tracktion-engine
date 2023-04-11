#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include "SineToneGenerator.hpp"

class SineTonePlayer
{
public:
    SineTonePlayer();
    ~SineTonePlayer();

    void startPlaying();
    void stopPlaying();
    void setFrequency(double frequency);

private:
    juce::AudioDeviceManager audioDeviceManager;
    SineToneGenerator sineToneGenerator;

    class SineToneSource : public juce::AudioIODeviceCallback
    {
    public:
        SineToneSource(SineToneGenerator& generator);

        void audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
                                          float* const* outputChannelData, int numOutputChannels,
                                          int numSamples,
                                          const juce::AudioIODeviceCallbackContext& context) override;

        void audioDeviceAboutToStart(juce::AudioIODevice* device) override;
        void audioDeviceStopped() override;

    private:
        SineToneGenerator& sineToneGenerator;
    };

    SineToneSource sineToneSource;
};
