cmake_minimum_required(VERSION 3.15)

project(DemoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE library
add_subdirectory(deps/JUCE)

# # Add the JUCE-based project
# juce_add_module(src/DemoEngine)

# Set up the DLL target
add_library(DemoEngine SHARED
    src/DemoEngine.hpp
    src/DemoEngine.cpp)

target_link_libraries(DemoEngine PRIVATE
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_audio_devices)

# Export symbols
target_compile_definitions(DemoEngine PRIVATE JUCE_DLL_BUILD=1)
