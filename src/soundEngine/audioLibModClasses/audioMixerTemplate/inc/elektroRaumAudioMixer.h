#pragma once

#include "arduinoLib.h"
#include "AudioStream.h"
#include "utility/dspinst.h"

template <size_t numberOfChannels>
class ElektroRaumAudioMixer : public AudioStream
{
public:
	ElektroRaumAudioMixer(): AudioStream(numberOfChannels, inputQueueArray)
	{
		for (uint32_t i{0}; i < numberOfChannels; i++)
		{
			multiplier[i] = 65536;
		}
	}

	virtual void update(void)
	{
		audio_block_t *in, *out=NULL;
		unsigned int channel;

		for (channel=0; channel < numberOfChannels; channel++) {
			if (!out) {
				out = receiveWritable(channel);
				if (out) {
					int32_t mult = multiplier[channel];
					if (mult != MULTI_UNITYGAIN) applyGain(out->data, mult);
				}
			} else {
				in = receiveReadOnly(channel);
				if (in) {
					applyGainThenAdd(out->data, in->data, multiplier[channel]);
					release(in);
				}
			}
		}
		if (out) {
			transmit(out);
			release(out);
		}
	}
	
	virtual void gain(uint32_t channel, float gain)
	{
		if (channel >= numberOfChannels)
		{
			return;
		}
		if (gain > 32767.0f)
		{
			gain = 32767.0f;
		}
		else if (gain < -32767.0f)
		{
			 gain = -32767.0f;
		}
		multiplier[channel] = static_cast<int32_t>(gain * 65536.0f);
	}

protected:

virtual void applyGain(int16_t *data, int32_t mult)
{
	uint32_t *p = (uint32_t *)data;
	const uint32_t *end = (uint32_t *)(data + AUDIO_BLOCK_SAMPLES);

	do {
		uint32_t tmp32 = *p; // read 2 samples from *data
		int32_t val1 = signed_multiply_32x16b(mult, tmp32);
		int32_t val2 = signed_multiply_32x16t(mult, tmp32);
		val1 = signed_saturate_rshift(val1, 16, 0);
		val2 = signed_saturate_rshift(val2, 16, 0);
		*p++ = pack_16b_16b(val2, val1);
	} while (p < end);
}

virtual void applyGainThenAdd(int16_t *data, const int16_t *in, int32_t mult)
{
	uint32_t *dst = (uint32_t *)data;
	const uint32_t *src = (uint32_t *)in;
	const uint32_t *end = (uint32_t *)(data + AUDIO_BLOCK_SAMPLES);

	if (mult == MULTI_UNITYGAIN) {
		do {
			uint32_t tmp32 = *dst;
			*dst++ = signed_add_16_and_16(tmp32, *src++);
			tmp32 = *dst;
			*dst++ = signed_add_16_and_16(tmp32, *src++);
		} while (dst < end);
	} else {
		do {
			uint32_t tmp32 = *src++; // read 2 samples from *data
			int32_t val1 = signed_multiply_32x16b(mult, tmp32);
			int32_t val2 = signed_multiply_32x16t(mult, tmp32);
			val1 = signed_saturate_rshift(val1, 16, 0);
			val2 = signed_saturate_rshift(val2, 16, 0);
			tmp32 = pack_16b_16b(val2, val1);
			uint32_t tmp32b = *dst;
			*dst++ = signed_add_16_and_16(tmp32, tmp32b);
		} while (dst < end);
	}
}

private:
	static constexpr uint32_t MULTI_UNITYGAIN{65536};
	int32_t multiplier[numberOfChannels];
	audio_block_t *inputQueueArray[numberOfChannels];
};
