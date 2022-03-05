#include "voiceOscillator.h"

VoiceOscillator::VoiceOscillator()
{
}

VoiceOscillator::~VoiceOscillator()
{
}

void VoiceOscillator::play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity)
{
    VoiceBase::play(midiChannel, midiNote, velocity);
    m_oscillator.begin(WAVEFORM_BANDLIMIT_SQUARE);
    m_oscillator.frequency(m_frequency);
    m_oscillator.amplitude(0.3f);
}

void VoiceOscillator::stop()
{
    VoiceBase::stop();
    m_oscillator.amplitude(0.0f);
}

