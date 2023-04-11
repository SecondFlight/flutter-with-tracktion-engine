#include "SineTonePlayer.hpp"

SineTonePlayer::SineTonePlayer() : sineToneSource(sineToneGenerator)
{
    audioDeviceManager.initialise(0, 2, nullptr, true);
}

SineTonePlayer::~SineTonePlayer()
{
    stopPlaying();
    audioDeviceManager.closeAudioDevice();
}

void SineTonePlayer::startPlaying()
{
    audioDeviceManager.addAudioCallback(&sineToneSource);
}

void SineTonePlayer::stopPlaying()
{
    audioDeviceManager.removeAudioCallback(&sineToneSource);
}

void SineTonePlayer::setFrequency(double frequency)
{
    sineToneGenerator.setFrequency(frequency);
}

SineTonePlayer::SineToneSource::SineToneSource(SineToneGenerator& generator)
    : sineToneGenerator(generator)
{
}

void SineTonePlayer::SineToneSource::audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
                                          float* const* outputChannelData, int numOutputChannels,
                                          int numSamples,
                                          const juce::AudioIODeviceCallbackContext& context)
{
    juce::AudioBuffer<float> buffer(outputChannelData, numOutputChannels, numSamples);
    sineToneGenerator.fillNextAudioBuffer(buffer);
}

void SineTonePlayer::SineToneSource::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
}

void SineTonePlayer::SineToneSource::audioDeviceStopped()
{
}
