#include "wave.h"
#include "int2chars.h"

#include <cstring>
#include <stdio.h>
#include <iostream>

Wave::Wave(uint16_t numChannels, uint32_t sampleRate, uint16_t bitsPerSample, uint32_t duration)
{
    // Header
    this->chunkID = "RIFF";
    this->chunkSize = 4 + (8 + 16) + (8 + numChannels * bitsPerSample * sampleRate * duration);
    this->format = "WAVE";

    // subChunkFMT
    this->subChunk1ID = "fmt ";
    this->subChunk1Size = 16;
    this->audioFormat = 1;
    this->numChannels = numChannels;
    this->sampleRate = sampleRate;
    this->bitsPerSample = bitsPerSample;
    this->byteRate = numChannels * bitsPerSample * sampleRate / 8;
    this->blockAlign = numChannels * bitsPerSample / 8;

    // subChunkDATA
    this->subChunk2ID = "data";
    this->subChunk2Size = numChannels * bitsPerSample * sampleRate * duration / 8;
}

Wave::~Wave()
{
}

void Wave::writeFile(std::string filename, char *data, size_t data_len)
{
    FILE *wf = fopen(filename.c_str(), "wb");
    // Header
    fwrite(this->chunkID.c_str(), 1, 4, wf); //以1byte为单位，写入4个单位
    fwrite(int32_2_chars(this->chunkSize), 1, 4, wf);
    fwrite(this->format.c_str(), 1, 4, wf);

    // subChunkFMT
    fwrite(this->subChunk1ID.c_str(), 1, 4, wf);
    fwrite(int32_2_chars(this->subChunk1Size), 1, 4, wf);
    fwrite(int16_2_chars(this->audioFormat), 1, 2, wf);
    fwrite(int16_2_chars(this->numChannels), 1, 2, wf);
    fwrite(int32_2_chars(this->sampleRate), 1, 4, wf);
    fwrite(int32_2_chars(this->byteRate), 1, 4, wf);
    fwrite(int16_2_chars(this->blockAlign), 1, 2, wf);
    fwrite(int16_2_chars(this->bitsPerSample), 1, 2, wf);

    // subChunkDATA
    fwrite(this->subChunk2ID.c_str(), 1, 4, wf);
    fwrite(int32_2_chars(this->subChunk2Size), 1, 4, wf);
    if (data)
    {
        fwrite(data, 1, data_len, wf);
    }
    else
    {
        std::cerr << "It seems that you didn't add any data...\n"
                  << std::endl;
    }
    fclose(wf);
}