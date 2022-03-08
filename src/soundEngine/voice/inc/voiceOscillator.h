#pragma once

#include "voiceBase.h"
#include "soundEngineDefs.h"
#include "dataHandler.h"

class VoiceOscillator : public VoiceBase
{
public:
    VoiceOscillator();
    virtual ~VoiceOscillator();
    virtual void play(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) override;
    virtual void stop() override;
    virtual void setWaveform();
    virtual void update();

protected:
    AudioSynthWaveformModulated m_oscillator;
    AudioConnection m_connections[1] = {
        AudioConnection(m_oscillator, 0, m_output, 0)
    };
    Waveform m_waveform;

private:
    uint32_t m_id;
    static uint32_t m_id_counter;
    static DataHandler m_dataHandler;
};
