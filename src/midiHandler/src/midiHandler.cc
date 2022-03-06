#include "midiHandler.h"
#include "soundEngineIf.h"
#include "arduinoLib.h"

bool MidiHandler::m_initialized{false};

SoundEngineIf* g_soundEnginePtr{nullptr};

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

void controlChange(const uint8_t channel, const uint8_t controller, const uint8_t data)
{
    if(g_soundEnginePtr)
    {
        g_soundEnginePtr->controlChange(channel, controller, data);
    }
}

MidiHandler::MidiHandler(SoundEngineIf& soundEngine)
{
    if (!m_initialized)
    {
        g_soundEnginePtr = &soundEngine;
        usbMIDI.setHandleNoteOn(noteOn);
        usbMIDI.setHandleNoteOff(noteOff);
        usbMIDI.setHandleControlChange(controlChange);
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
