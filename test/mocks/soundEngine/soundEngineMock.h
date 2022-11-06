#include "soundEngineIf.h"
#include "gmock/gmock.h"

class SoundEngineMock : public SoundEngineIf
{
public:
    SoundEngineMock(){};
    virtual ~SoundEngineMock(){};
    MOCK_METHOD(void, update, (), (const, override));
    MOCK_METHOD(void, noteOn, (uint8_t, uint8_t, uint8_t), (const, override));
    MOCK_METHOD(void, noteOff, (uint8_t, uint8_t, uint8_t), (const, override));
    MOCK_METHOD(void, controlChange, (uint8_t, uint8_t, uint8_t), (const, override));
    MOCK_METHOD(void, initialize, (), (override));
};