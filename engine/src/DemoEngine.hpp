#pragma once

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_audio_devices/juce_audio_devices.h>

#if JUCE_WINDOWS
    #define SINE_TONE_DLL_EXPORT __declspec(dllexport)
#else
    #define SINE_TONE_DLL_EXPORT __attribute__((visibility("default")))
#endif

class SINE_TONE_DLL_EXPORT SineTone
{
public:
    SineTone(double frequency, double sampleRate);
    float getNextSample();

private:
    double frequency;
    double sampleRate;
    double phase;
    double phaseDelta;
};
