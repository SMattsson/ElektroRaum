#pragma once

#include <stdint.h>

class SoundEngineIf
{
public:
    SoundEngineIf(){};
    virtual ~SoundEngineIf(){};
    virtual void noteOn(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const = 0;
    virtual void noteOff(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const = 0;
    virtual void controlChange(const uint8_t channel, const uint8_t controller, const uint8_t data) const = 0;
    virtual void update() const = 0;

protected:
    virtual void initialize() = 0;
};
