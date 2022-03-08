/*
 * Simple polyphonic synth
*/

#include <vector>
#include "soundEngine.h"
#include "midiHandler.h"
#include "dataHandler.h"
#include "serialHandler.h"
#include "arduinoLib.h"

int main()
{
    DataHandler dataHandler;
    SoundEngine soundEngine;
    MidiHandler midiHandler(soundEngine);
    SerialHandler serialHandler(dataHandler);

    uint32_t previousMillis = 0;
    while (true)
    {
        midiHandler.update();
        serialHandler.update();
        soundEngine.update();
        if (millis() - previousMillis > 100)
        {
            previousMillis = millis();
            digitalWrite(13, !digitalRead(13));
        }
    }

    return 0;
}
