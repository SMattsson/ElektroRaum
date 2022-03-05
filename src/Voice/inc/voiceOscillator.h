#pragma once

#include "voiceBase.h"

class VoiceOscillator : public VoiceBase
{
public:
    VoiceOscillator();
    virtual ~VoiceOscillator();
    void play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) final override;
    void stop() final override;

protected:
    AudioSynthWaveformModulated m_oscillator;
    AudioConnection m_connections[1] = {
        AudioConnection(m_oscillator, 0, m_output, 0)
    };
};