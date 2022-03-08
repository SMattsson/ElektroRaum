#pragma once

#include <vector>
#include "soundEngineIf.h"
#include "audioLib.h"
#include "voiceIf.h"
#include "voiceOscillator.h"
#include "soundEngineCfg.h"
#include "elektroRaumAudioMixer.h"
#include "dataHandler.h"


class SoundEngine : public SoundEngineIf
{
public:
    SoundEngine();
    virtual ~SoundEngine();
    virtual void noteOn(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const override;
    virtual void noteOff(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const override;
    virtual void controlChange(const uint8_t channel, const uint8_t controller, const uint8_t data) const override;
    virtual void update() const override;

protected:
    virtual void initialize();

private:
    static std::vector<VoiceOscillator*> m_voiceOscillators;
    static std::vector<VoiceIf*> m_voices;
    static std::vector<AudioConnection*> m_audioConnections;
    static SoundEngineCfg::MasterOutDevice m_masterOutDevice;
    static ElektroRaumAudioMixer<SoundEngineCfg::NUMBER_OF_VOICES> m_outputMixer;
    static DataHandler m_dataHandler;
    static bool m_initialized;
};
