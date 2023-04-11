cmake_minimum_required(VERSION 3.15)

project(DemoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE library
add_subdirectory(deps/JUCE)

# Set up the DLL target
add_library(DemoEngine SHARED
    src/main.cpp
    src/SineToneGenerator.cpp
    src/SineToneGenerator.hpp
    src/SineTonePlayer.cpp
    src/SineTonePlayer.hpp)

target_include_directories(DemoEngine PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(DemoEngine PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core)

# Export symbols
target_compile_definitions(DemoEngine PRIVATE JUCE_DLL_BUILD=1 JUCE_DLL=1)

# Set target properties to build it as a shared library
set_target_properties(DemoEngine PROPERTIES
    BUNDLE_EXTENSION "dll"
    SUFFIX ".dll"
    OUTPUT_NAME "DemoEngine"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
