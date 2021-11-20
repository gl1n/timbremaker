#include "sin.h"
#include <math.h>
#include <iostream>

double PI = 3.1415926535897932384626;

void sin(uint16_t numChannels, uint32_t sampleRate, uint32_t bitPerSample, uint32_t duration, uint32_t base_freq, std::vector<int> harmonic_weight, char **data_ptr, int *data_len)
{
    double tau = 1 / double(sampleRate);
    if (numChannels == 1)
    {
        uint32_t numSamples = sampleRate * duration;
        char *data = (char *)malloc(bitPerSample / 8 * numSamples);
        *data_len = bitPerSample / 8 * numSamples;
        for (uint32_t i = 0; i < numSamples; i++)
        {
            double t = tau * i;

            int weight_sum = 0;
            double A = 0; //用来保存叠加的采样
            for (size_t i = 0; i < harmonic_weight.size(); i++)
            {
                A += harmonic_weight[i] * sin(2 * PI * (base_freq * (i + 1)) * t);
                weight_sum += harmonic_weight[i];
            }
            uint16_t uA = uint16_t(A / weight_sum * 32767);

            //按小端的方式写入
            data[i * 2] = uA;
            data[i * 2 + 1] = uA >> 8;
        }
        *data_ptr = data;
    }
    else
    {
        std::cerr << "Monoo mode has been implemented only..." << std::endl;
        *data_len = 0;
        *data_ptr = nullptr;
    }
}