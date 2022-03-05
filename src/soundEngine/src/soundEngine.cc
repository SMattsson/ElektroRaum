#include "soundEngine.h"
#include "midiLib.h"

std::vector<VoiceOscillator*> SoundEngine::m_voiceOscillators;
std::vector<VoiceIf*> SoundEngine::m_voices;
std::vector<AudioConnection*> SoundEngine::m_audioConnections;
SoundEngineCfg::MasterOutDevice SoundEngine::m_masterOutDevice;
AudioMixer4 SoundEngine::m_outputMixer;
bool SoundEngine::m_initialized{false};

SoundEngine::SoundEngine()
{
    if(!m_initialized)
    {
        initialize();
    }
}

SoundEngine::~SoundEngine()
{

}

void SoundEngine::initialize()
{
    AudioMemory(SoundEngineCfg::AUDIO_MEMORY_BLOCKS);
    m_voiceOscillators.reserve(SoundEngineCfg::NUMBER_OF_VOICES);
    m_voices.reserve(SoundEngineCfg::NUMBER_OF_VOICES);
    m_audioConnections.reserve(SoundEngineCfg::NUMBER_OF_VOICES + 2);

    for (size_t i{0}; i < SoundEngineCfg::NUMBER_OF_VOICES; i++)
    {
        m_voiceOscillators.push_back(new VoiceOscillator());
    }

    for (auto& voiceOscillator : m_voiceOscillators)
    {
        m_voices.push_back(voiceOscillator);
    }

    {
        uint8_t channel{0};
        for (auto& voice : m_voices)
        {
            m_audioConnections.push_back(new AudioConnection(voice->getOutput(), 0, m_outputMixer, channel));
            channel++;
        }
    }

    m_audioConnections.push_back(new AudioConnection(m_outputMixer, 0, m_masterOutDevice, 0));
    m_audioConnections.push_back(new AudioConnection(m_outputMixer, 0, m_masterOutDevice, 1));
    m_initialized = true;
}

void SoundEngine::noteOn(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const
{
    for (const auto& voice : m_voices)
    {
        if (voice->isIdle() && midiChannel != 10)
        {
            voice->play(midiChannel, midiNote, velocity);
            return;
        }
    }
}

void SoundEngine::noteOff(const uint8_t midiChannel, const uint8_t midiNote, __attribute__((unused))const uint8_t velocity) const
{
    for (const auto& voice : m_voices)
    {
        if (!voice->isIdle() &&
            midiChannel == voice->getMidiChannel() &&
            midiNote == voice->getMidiNote())
        {
            voice->stop();
            return;
        }
    }
}

void SoundEngine::controlChange(const uint8_t channel, const uint8_t controller, const uint8_t data) const
{
    switch (controller)
    {
    case MIDI_NAMESPACE::MidiControlChangeNumber::AllSoundOff:
        for (const auto &voice : m_voices)
        {
            if (voice->getMidiChannel() == channel)
            {
                voice->stop();
            }
        }
        break;
    case MIDI_NAMESPACE::MidiControlChangeNumber::AllNotesOff:
        for (const auto &voice : m_voices)
        {
            if (voice->getMidiChannel() == channel)
            {
                voice->stop();
            }
        }
        break;
    default:;
    }
}
