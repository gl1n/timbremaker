#include "sin.h"
#include <math.h>
#include <iostream>

double PI = 3.1415926535897932384626;

void sin(uint16_t numChannels, uint32_t sampleRate, uint32_t bitPerSample, uint32_t duration, uint32_t base_freq, double second_w, double third_w, char **data_ptr, int *data_len)
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

            double base_A = sin(2 * PI * base_freq * t);                  //基波
            double second_A = second_w * sin(2 * PI * base_freq * 2 * t); //一次泛音
            double third_A = third_w * sin(2 * PI * base_freq * 3 * t);   //二次泛音
            uint16_t A = uint16_t(32767 * (base_A + second_A + third_A) / (1 + second_w + third_w));

            //按小端的方式写入
            data[i * 2] = A;
            data[i * 2 + 1] = A >> 8;
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