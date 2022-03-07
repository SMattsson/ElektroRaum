#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "arduinoLib.h"
#include "midiHandler.h"
#include "soundEngineMock.h"

using ::testing::StrictMock;
using ::testing::Mock;
using ::testing::_;

UsbMIDIStubWithMock usbMIDI;

class MidiHandlerTest : public ::testing::Test
{
public:
    virtual ~MidiHandlerTest();
    virtual void SetUp() override;
    virtual void TearDown() override;
};

MidiHandlerTest::~MidiHandlerTest()
{
    Mock::VerifyAndClearExpectations(&usbMIDI);
}

void MidiHandlerTest::SetUp()
{
}

void MidiHandlerTest::TearDown()
{
}

TEST_F(MidiHandlerTest, initalizationTest)
{
    StrictMock<SoundEngineMock> soundEngineMock;
    StrictMock<UsbMIDIMock> usbMIDIMock;
    usbMIDI.setMock(&usbMIDIMock);
    
    EXPECT_CALL(usbMIDIMock, setHandleNoteOn(_)).Times(1);
    EXPECT_CALL(usbMIDIMock, setHandleNoteOff(_)).Times(1);
    EXPECT_CALL(usbMIDIMock, setHandleControlChange(_)).Times(1);
    MidiHandler MidiHandler(soundEngineMock);
}
