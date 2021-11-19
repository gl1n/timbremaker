#include <inttypes.h>
#include <string>

class Wave
{
private:
    // Header
    std::string chunkID;
    uint32_t chunkSize;
    std::string format;

    // subChunkFMT
    std::string subChunk1ID; // 0x666d7420(fmt )
    uint32_t subChunk1Size;  // PCM=16
    uint16_t audioFormat;    // PCM=1
    uint16_t numChannels;    // Mono=1,Stereo=2
    uint32_t sampleRate;     // 8000, 44100...
    uint32_t byteRate;       // SampleRate*NumChannels*BitsPerSample/8
    uint16_t blockAlign;     // NumChannels * BitsPerSample / 8
    uint16_t bitsPerSample;  // 8, 16...
    // ExtraParamSize uint16  //如果是PCM的话这个字段就不需要了
    // ExtraParams

    // subChunkDATA
    std::string subChunk2ID; // 0x64617461(data)
    uint32_t subChunk2Size;  // NumSamples * NumChannels * BitsPerSample / 8
    // char *data;              // 音频数据

public:
    Wave(uint16_t numChannels, uint32_t sampleRate, uint16_t bitsPerSample, uint32_t duration);
    ~Wave();

    void writeFile(std::string, char *, size_t);
};