#pragma once

#include "audioLib.h"
#include "voiceIf.h"

class VoiceBase : public VoiceIf
{
public:
    VoiceBase();
    virtual ~VoiceBase();
    virtual void play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) override;
    virtual void stop() override;
    bool isIdle() const final override;
    uint8_t getMidiChannel() const final override;
    uint8_t getMidiNote() const final override;
    uint8_t getVelocity() const final override;
    AudioAmplifier& getOutput() final override;

protected:
    VoiceState m_currentState;
    uint8_t m_midiChannel;
    uint8_t m_midiNote;
    uint8_t m_velocity;
    float m_frequency;
    AudioAmplifier m_output;
};
