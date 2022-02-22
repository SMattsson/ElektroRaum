#include <Arduino.h>
#include <Audio.h>

/*
 * Simple build test with Audio library
*/

int main()
{
    AudioSynthWaveformModulated waveform;
    AudioOutputI2S2 output;
    AudioConnection patchCord1(waveform, 0, output, 0);
    AudioConnection patchCord2(waveform, 0, output, 1);

    //Baudrate doesn't matter as it's "emulated serial" trough USB,
    //and always runs at USB speeds (up to 480Mbits/s).
    Serial.begin(115200);

    //Wait for host to connect a serial terminal to Teensy.
    while (!Serial)
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(500);
    }

    return 0;
}
