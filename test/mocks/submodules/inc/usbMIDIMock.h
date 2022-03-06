#include <gmock/gmock.h>
#include <gtest/gtest.h>

class UsbMIDIMock
{
public:
    MOCK_METHOD(void, setHandleNoteOn, (void (*)(uint8_t, uint8_t, uint8_t)));
    MOCK_METHOD(void, setHandleNoteOff, (void (*)(uint8_t, uint8_t, uint8_t)));
    MOCK_METHOD(void, setHandleControlChange, (void (*)(uint8_t, uint8_t, uint8_t)));
    MOCK_METHOD(void, read, ());
};

class UsbMIDIStubWithMock
{
public:
    void setMock(UsbMIDIMock* usbMIDIMockPtr)
    {
        m_usbMIDIMockPtr = usbMIDIMockPtr;
    }

    void setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity))
    {
        ASSERT_FALSE(m_usbMIDIMockPtr == nullptr);
        m_usbMIDIMockPtr->setHandleNoteOn(fptr);
    }

    void setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity))
    {
        ASSERT_FALSE(m_usbMIDIMockPtr == nullptr);
        m_usbMIDIMockPtr->setHandleNoteOff(fptr);
    }

    void setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t control, uint8_t value))
    {
        ASSERT_FALSE(m_usbMIDIMockPtr == nullptr);
        m_usbMIDIMockPtr->setHandleControlChange(fptr);
    }

    void read()
    {
        ASSERT_FALSE(m_usbMIDIMockPtr == nullptr);
        m_usbMIDIMockPtr->read();
    }
    
private:
    UsbMIDIMock* m_usbMIDIMockPtr = nullptr;
};

extern UsbMIDIStubWithMock usbMIDI;