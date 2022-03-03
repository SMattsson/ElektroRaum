#include <Arduino.h>
#include <Audio.h>
#include <MIDI.h>
#include "audioUtils.h"

/*
 * Simple build test with Audio library
*/

AudioSynthWaveformModulated waveform;
AudioOutputI2S2 output; //NOTE: Using the I2S2
AudioUtils audioUtils;
bool noteFree{true};

void noteOn(uint8_t midiChannel, uint8_t midiNote, uint8_t velocity)
{
    if (noteFree)
    {
        waveform.amplitude(1.0f);
        waveform.frequency(audioUtils.getFrequencyFromMidiNote(midiNote));
        noteFree = false;
    }

}

void noteOff(uint8_t midiChannel, uint8_t midiNote, uint8_t velocity)
{
    waveform.amplitude(0.0f);
    noteFree = true;
}

int main()
{
    AudioMemory(16);
    AudioConnection patchCord1(waveform, 0, output, 0);
    AudioConnection patchCord2(waveform, 0, output, 1);

    usbMIDI.setHandleNoteOn(noteOn);
    usbMIDI.setHandleNoteOff(noteOff);

    waveform.begin(WAVEFORM_SQUARE);

    //Baudrate doesn't matter as it's "emulated serial" trough USB,
    //and always runs at USB speeds (up to 480Mbits/s).
    Serial.begin(115200);

    //Wait for host to connect a serial terminal to Teensy.
    while (true)
    {
        usbMIDI.read();
    }

    return 0;
}
