/*
 * Simple polyphonic synth
*/

#include <vector>
#include "soundEngine.h"
#include "midiHandler.h"
#include "audioLib.h"
#include "audioUtils.h"
#include "voiceOscillator.h"

int main()
{
    SoundEngine soundEngine;
    MidiHandler midiHandler(soundEngine);

    //Baudrate doesn't matter as it's "emulated serial" trough USB,
    //and always runs at USB speeds (up to 480Mbits/s).
    Serial.begin(115200);

    uint32_t previousMillis = 0;
    while (true)
    {
        midiHandler.update();
        if (millis() - previousMillis > 100)
        {
            previousMillis = millis();
            digitalWrite(13, !digitalRead(13));
        }
    }

    return 0;
}
