#include "daisy_pod.h"
#include "daisysp.h"
#include "ImpulseResponse.h"

using namespace daisy;
using namespace daisysp;

DaisyPod hw;



void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t sizeBuffer)
{
	hw.ProcessAllControls();

	auto impulseResponse = getImpulseResponse();

	float* h = impulseResponse.first;
	int sizeImpulse = impulseResponse.second;
	

	for (size_t i = 0; i < sizeBuffer; i++)
	{
		for (int j = 0; j < sizeImpulse; i++)
		{
			out[0][i] = 0.f;
			out[1][i] = 0.f;

			if (!((i-j < 0) || i-j > sizeBuffer) && hw.button1.Pressed())
			{
				out[0][i] = out[0][i] + h[0][j] * in[0][i-j];
				out[1][i] = out[1][i] + h[1][j] * in[1][i-j];
			}
			else
			{
				out[0][i] = in[0][i];
				out[1][i] = in[1][i];
			}
		}
	}
}

int main(void)
{
	hw.Init();		
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	while(1) {}
}
