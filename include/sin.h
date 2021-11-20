#include <vector>
#include <inttypes.h>
// base_freq是基波的频率，second_w是一次泛音振幅与基波的比，third_w是二次泛音振幅与基波的比
void sin(uint16_t numChannels, uint32_t sampleRate, uint32_t bitPerSample, uint32_t duration, uint32_t base_freq, std::vector<int> harmonic, char **data_ptr, int *data_len);