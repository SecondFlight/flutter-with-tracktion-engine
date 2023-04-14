cmake_minimum_required(VERSION 3.15)

project(DemoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE library
add_subdirectory(deps/JUCE)
add_subdirectory(deps/tracktion-engine)

# Set up the DLL target
juce_add_console_app(DemoEngine SHARED
    src/main.cpp
    src/SineToneGenerator.cpp
    src/SineToneGenerator.hpp
    src/SineTonePlayer.cpp
    src/SineTonePlayer.hpp)

target_include_directories(DemoEngine PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(DemoEngine
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    tracktion::tracktion_engine

    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

# Export symbols
target_compile_definitions(DemoEngine PRIVATE JUCE_DLL_BUILD=1 JUCE_DLL=1 JUCE_DISABLE_CUSTOM_ALLOCATOR=1)
