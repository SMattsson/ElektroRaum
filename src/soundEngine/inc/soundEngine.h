#pragma once

#include <vector>
#include "audioLib.h"
#include "voiceIf.h"
#include "voiceOscillator.h"
#include "SoundEngineCfg.h"

class SoundEngine
{
public:
    SoundEngine();
    virtual ~SoundEngine();
    virtual void noteOn(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const;
    virtual void noteOff(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity) const;
    virtual void controlChange(const uint8_t channel, const uint8_t controller, const uint8_t data) const;

protected:
    virtual void initialize();

private:
    static std::vector<VoiceOscillator*> m_voiceOscillators;
    static std::vector<VoiceIf*> m_voices;
    static std::vector<AudioConnection*> m_audioConnections;
    static SoundEngineCfg::MasterOutDevice m_masterOutDevice;
    static AudioMixer4 m_outputMixer;
    static bool m_initialized;
};
