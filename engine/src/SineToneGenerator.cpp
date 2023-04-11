#include "SineToneGenerator.hpp"

SineToneGenerator::SineToneGenerator()
    : currentFrequency(440.0), currentAngle(0.0), angleDelta(0.0), sampleRate(44100.0)
{
    setFrequency(currentFrequency);
}

void SineToneGenerator::setFrequency(double frequency)
{
    currentFrequency = frequency;
    angleDelta = 2.0 * juce::MathConstants<double>::pi * currentFrequency / sampleRate;
}

void SineToneGenerator::fillNextAudioBuffer(juce::AudioBuffer<float>& buffer)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    for (auto channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (auto sample = 0; sample < numSamples; ++sample)
        {
            auto currentSample = (float)std::sin(currentAngle);
            channelData[sample] = currentSample;
            currentAngle += angleDelta;
        }
    }
}
