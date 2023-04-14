cmake_minimum_required(VERSION 3.15)

project(DemoEngine VERSION 0.0.1)

add_subdirectory(deps)

juce_add_console_app(DemoEngine SHARED)

add_subdirectory(src)

# Link against JUCE and Tracktion engine
target_link_libraries(
  DemoEngine

  PRIVATE
  juce::juce_audio_utils
  tracktion::tracktion_engine

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)
