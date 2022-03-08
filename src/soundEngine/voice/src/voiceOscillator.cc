#include "voiceOscillator.h"
#include "soundEngineCfg.h"

uint32_t VoiceOscillator::m_id_counter={0};
DataHandler VoiceOscillator ::m_dataHandler;

VoiceOscillator::VoiceOscillator() : m_waveform(Waveform::SINE), m_id(m_id_counter++)
{
}

VoiceOscillator::~VoiceOscillator()
{
}

void VoiceOscillator::play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity)
{
    VoiceBase::play(midiChannel, midiNote, velocity);
    setWaveform();
    m_oscillator.frequency(m_frequency);
    m_oscillator.amplitude(SoundEngineCfg::MAX_VOICE_VOLUME);
}

void VoiceOscillator::stop()
{
    VoiceBase::stop();
    m_oscillator.amplitude(0.0f);
}

void VoiceOscillator::setWaveform()
{
    auto waveform = m_dataHandler.getParameter(Parameter::OSCILLATOR_0_WAVEFORM);
    if (waveform)
    {
        if (m_waveform != static_cast<Waveform>(waveform.value()))
        {
            m_waveform = static_cast<Waveform>(waveform.value());
            m_oscillator.begin(static_cast<int16_t>(m_waveform));
        }
    }
}

void VoiceOscillator::update()
{
    setWaveform();
}
