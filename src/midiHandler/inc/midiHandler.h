#pragma once

class SoundEngineIf;

class MidiHandler
{
public:
    MidiHandler(SoundEngineIf& soundEngine);
    virtual ~MidiHandler();
    virtual void update();

private:
    static bool m_initialized;
};
