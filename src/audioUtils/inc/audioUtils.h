#pragma once

#include <math.h>
#include <stdint.h>
#include <array>

class AudioUtils
{
public:
    AudioUtils();
    virtual ~AudioUtils();
    virtual float getFrequencyFromMidiNote(const uint8_t midiNote) const;

private:
    static constexpr size_t NUMBER_OF_MIDI_NOTES{UINT8_MAX};
    static std::array<float, NUMBER_OF_MIDI_NOTES> m_midiNoteToFrequencyArray; 
    static bool m_initialized;
};
