#include <array>
#include "audioLib.h"
#include "audioUtils.h"
#include "voiceOscillator.h"

/*
 * Simple polyphonic synth
*/

std::array<VoiceOscillator, 4> voices;

AudioOutputI2S2 finalOutput; //NOTE: Using the I2S2
AudioMixer4 mixer;
AudioUtils audioUtils;

AudioConnection connections[6]
{
    AudioConnection(voices[0].getOutput(), 0, mixer, 0),
    AudioConnection(voices[1].getOutput(), 0, mixer, 1),
    AudioConnection(voices[2].getOutput(), 0, mixer, 2),
    AudioConnection(voices[3].getOutput(), 0, mixer, 3),
    AudioConnection(mixer, 0, finalOutput, 0),
    AudioConnection(mixer, 0, finalOutput, 1)
};

void noteOn(uint8_t midiChannel, uint8_t midiNote, uint8_t velocity)
{
    for (auto& voice : voices)
    {
        if (voice.isIdle() && midiChannel != 10)
        {
            voice.play(midiChannel, midiNote, velocity);
            return;
        }
    }
}

void noteOff(uint8_t midiChannel, uint8_t midiNote, uint8_t velocity)
{
    for (auto& voice : voices)
    {
        if (!voice.isIdle() && 
            midiChannel == voice.getMidiChannel() &&
            midiNote == voice.getMidiNote())
        {
            voice.stop();
            return;
        }
    }
}

int main()
{
    AudioMemory(32);

    usbMIDI.setHandleNoteOn(noteOn);
    usbMIDI.setHandleNoteOff(noteOff);

    //Baudrate doesn't matter as it's "emulated serial" trough USB,
    //and always runs at USB speeds (up to 480Mbits/s).
    Serial.begin(115200);

    while (true)
    {
        usbMIDI.read();
    }

    return 0;
}
