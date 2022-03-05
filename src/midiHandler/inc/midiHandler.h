#pragma once

class SoundEngine;

class MidiHandler
{
public:
    MidiHandler(SoundEngine& soundEngine);
    virtual ~MidiHandler();
    virtual void update();

private:
    static bool m_initialized;
};
