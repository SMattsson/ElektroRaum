#include "midiHandler.h"
#include "soundEngine.h"

bool MidiHandler::m_initialized{false};

SoundEngine* g_soundEnginePtr{nullptr};

void noteOn(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity)
{
    if(g_soundEnginePtr)
    {
        g_soundEnginePtr->noteOn(midiChannel, midiNote, velocity);
    }
}

void noteOff(const uint8_t midiChannel, const uint8_t midiNote, const uint8_t velocity)
{
    if(g_soundEnginePtr)
    {
        g_soundEnginePtr->noteOff(midiChannel, midiNote, velocity);
    }
}

MidiHandler::MidiHandler(SoundEngine& soundEngine)
{
    if (!m_initialized)
    {
        g_soundEnginePtr = &soundEngine;
        usbMIDI.setHandleNoteOn(noteOn);
        usbMIDI.setHandleNoteOff(noteOff);
        m_initialized = true;
    }
}

MidiHandler::~MidiHandler()
{
}

void MidiHandler::update()
{
    usbMIDI.read();
}
