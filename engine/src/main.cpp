#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include "SineTonePlayer.hpp"

extern "C"
{
    __declspec(dllexport) SineTonePlayer* __stdcall createSineTonePlayer()
    {
        return new SineTonePlayer();
    }

    __declspec(dllexport) void __stdcall destroySineTonePlayer(SineTonePlayer* player)
    {
        delete player;
    }

    __declspec(dllexport) void __stdcall startPlaying(SineTonePlayer* player)
    {
        player->startPlaying();
    }

    __declspec(dllexport) void __stdcall stopPlaying(SineTonePlayer* player)
    {
        player->stopPlaying();
    }

    __declspec(dllexport) void __stdcall setFrequency(SineTonePlayer* player, double frequency)
    {
        player->setFrequency(frequency);
    }
}
