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
    virtual bool isIdle() const override;
    virtual uint8_t getMidiChannel() const override;
    virtual uint8_t getMidiNote() const override;
    virtual uint8_t getVelocity() const override;
    AudioAmplifier& getOutput() override;

protected:
    VoiceState m_currentState;
    uint8_t m_midiChannel;
    uint8_t m_midiNote;
    uint8_t m_velocity;
    float m_frequency;
    AudioAmplifier m_output;
};
