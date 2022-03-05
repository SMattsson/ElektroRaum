#include "audioUtils.h"

std::array<float, AudioUtils::NUMBER_OF_MIDI_NOTES> AudioUtils::m_midiNoteToFrequencyArray;
bool AudioUtils::m_initialized{false};

AudioUtils::AudioUtils()
{
    if(!m_initialized)
    {
        uint8_t midiNote{0};
        for (auto &freq : m_midiNoteToFrequencyArray)
        {
            freq = powf(2.0, (static_cast<float>(midiNote) - 69.0f) / 12.0f) * 440.0f;
            midiNote++;
        }
        m_initialized = true;
    }
};

AudioUtils::~AudioUtils()
{
};

float AudioUtils::getFrequencyFromMidiNote(const uint8_t midiNote) const
{
    return m_midiNoteToFrequencyArray[midiNote];
}