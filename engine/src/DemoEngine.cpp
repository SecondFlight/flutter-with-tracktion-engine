#include "DemoEngine.hpp"

SineTone::SineTone(double frequency, double sampleRate)
    : frequency(frequency), sampleRate(sampleRate), phase(0.0)
{
    phaseDelta = 2.0 * juce::MathConstants<double>::pi * frequency / sampleRate;
}

float SineTone::getNextSample()
{
    float sample = std::sin(phase);
    phase += phaseDelta;

    if (phase >= 2.0 * juce::MathConstants<double>::pi)
        phase -= 2.0 * juce::MathConstants<double>::pi;

    return sample;
}
