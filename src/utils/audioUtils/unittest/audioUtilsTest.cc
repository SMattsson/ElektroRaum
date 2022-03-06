#include "gtest/gtest.h"
#include "audioUtils.h"

class AudioUtilsTest : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;
};

void AudioUtilsTest::SetUp()
{
}

void AudioUtilsTest::TearDown()
{
}

TEST_F(AudioUtilsTest, VerifyFunction_getFrequencyFromMidiNote)
{
    AudioUtils audioUtils;
    EXPECT_FLOAT_EQ(3520.0f, audioUtils.getFrequencyFromMidiNote(105));     //B5
    EXPECT_FLOAT_EQ(440.0f, audioUtils.getFrequencyFromMidiNote(69));       //A4
    EXPECT_FLOAT_EQ(220.0f, audioUtils.getFrequencyFromMidiNote(57));       //A3
    EXPECT_FLOAT_EQ(97.998848f, audioUtils.getFrequencyFromMidiNote(43));   //G2
}
