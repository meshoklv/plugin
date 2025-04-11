cmake_minimum_required(VERSION 3.15)

project(SerumLite)

set(CMAKE_CXX_STANDARD 17)

# JUCE Setup
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/JUCE")
add_subdirectory(${JUCE_DIR})

juce_add_plugin(SerumLite
    COMPANY_NAME "YourCompany"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE Slit
    FORMATS VST3
    PRODUCT_NAME "SerumLite"
)

target_sources(SerumLite PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_compile_definitions(SerumLite PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(SerumLite PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra
)
