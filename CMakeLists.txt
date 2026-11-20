cmake_minimum_required(VERSION 3.22)

project(Yfaverb VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# JUCE lives in a git submodule. This makes the juce_add_plugin() function
# and the juce::juce_* module targets available.
add_subdirectory(JUCE)

#------------------------------------------------------------------------------
# DSP engine: plain C++, no JUCE. Shared by the CLI test tool and the plugin.
#------------------------------------------------------------------------------
add_library(YfaverbEngine STATIC
    ModeBank.cpp
    Mode.cpp
    ModalReverbEngine.cpp
)
target_include_directories(YfaverbEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# The plugin is a shared library (bundle), so code linked into it must be PIC.
set_target_properties(YfaverbEngine PROPERTIES POSITION_INDEPENDENT_CODE ON)

#------------------------------------------------------------------------------
# Offline test tool: renders an impulse through the engine to out.wav.
#------------------------------------------------------------------------------
add_executable(YfaverbCLI main.cpp)
target_link_libraries(YfaverbCLI PRIVATE YfaverbEngine)

#------------------------------------------------------------------------------
# Audio plugin. Creates the targets YfaverbPlugin_VST3, YfaverbPlugin_AU and
# YfaverbPlugin_Standalone, plus the shared-code target YfaverbPlugin.
#------------------------------------------------------------------------------
juce_add_plugin(YfaverbPlugin
    COMPANY_NAME "Yfaverb"
    PLUGIN_MANUFACTURER_CODE Yfvr      # 4 chars, at least one upper-case
    PLUGIN_CODE Yfv1                   # 4 chars, exactly one upper-case
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "Yfaverb"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE      # TRUE copies into ~/Library/Audio/Plug-Ins for DAW testing
    NEEDS_WEB_BROWSER FALSE
    NEEDS_CURL FALSE)

target_sources(YfaverbPlugin PRIVATE
    Plugin/PluginProcessor.cpp
)

target_compile_definitions(YfaverbPlugin PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(YfaverbPlugin
    PRIVATE
        YfaverbEngine
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
