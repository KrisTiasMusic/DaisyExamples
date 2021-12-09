#include "daisy_pod.h"
#include "daisysp.h"
#include "ImpulseResponse.h"

using namespace daisy;
using namespace daisysp;

DaisyPod hw;

int sizeImpulse = sizeof(impulseResponse[0]) / sizeof(float);

float* hL = impulseResponse[0];
float* hR = impulseResponse[1];

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t sizeBuffer)
{
	hw.ProcessAllControls();
	
	

	for (size_t i = 0; i < sizeBuffer; i++)
	{
		// out[0][i] = in[0][i];
		// out[1][i] = in[1][i];
		out[0][i] = 0.f;
		out[1][i] = 0.f;
		

		for (int j = 0; j < sizeImpulse; j++)
		{
			
			if (!((i-j < 0) || i-j > sizeBuffer) && hw.button1.Pressed())
			{
				out[0][i] = out[0][i]; + hL[j] * in[0][i-j];
				out[1][i] = out[1][i]; + hR[j] * in[1][i-j];
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
