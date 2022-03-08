#pragma once

enum class Waveform
{
    PULSE = 12,
    SAWTOOTH = 9,
    SAWTOOTH_REVERSE = 10,
    TRIANGLE = 8,
    SINE = 0
};

enum class Parameter
{
    OSCILLATOR_0_ACTIVE,
    OSCILLATOR_0_WAVEFORM,
    OSCILLATOR_0_PITCH,
    NUMBER_OF_PARAMETERS
};