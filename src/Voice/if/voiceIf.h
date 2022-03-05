#pragma once

#include "audioLib.h"

class VoiceIf
{
public:
    VoiceIf(){};
    virtual void play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) = 0;
    virtual void stop() = 0;
    virtual bool isIdle() const = 0;
    virtual uint8_t getMidiChannel() const = 0;
    virtual uint8_t getMidiNote() const = 0;
    virtual uint8_t getVelocity() const = 0;
    virtual AudioAmplifier& getOutput() = 0;

protected:
    enum class VoiceState{IDLE, PLAYING, RELEASED};
};