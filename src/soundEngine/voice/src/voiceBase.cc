#include "voiceBase.h"
#include "audioUtils.h"

VoiceBase::VoiceBase() : m_currentState(VoiceState::IDLE)
{

}

VoiceBase::~VoiceBase()
{

}

void VoiceBase::play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity)
{
    m_currentState = VoiceState::PLAYING;
    m_midiChannel = midiChannel;
    m_midiNote = midiNote;
    m_velocity = velocity;
    AudioUtils audioUtils;
    m_frequency = audioUtils.getFrequencyFromMidiNote(midiNote);
}

void VoiceBase::stop()
{
    m_currentState = VoiceState::IDLE;
}

bool VoiceBase::isIdle() const
{
    if (m_currentState == VoiceState::IDLE)
    {
        return true;
    }
    return false;
}

uint8_t VoiceBase::getMidiChannel() const
{
    return m_midiChannel;
}

uint8_t VoiceBase::getMidiNote() const
{
    return m_midiNote;
}

uint8_t VoiceBase::getVelocity() const
{
    return m_velocity;
}

AudioAmplifier& VoiceBase::getOutput()
{
    return m_output;
}