#pragma once

#include "audioLib.h"

namespace SoundEngineCfg
{
    constexpr size_t AUDIO_MEMORY_BLOCKS{128};  //N * 260bytes memory usage
    constexpr uint32_t NUMBER_OF_VOICES{4};     //Max 4 at the moment
    using MasterOutDevice = AudioOutputI2S2;    //NOTE I2S2
}
