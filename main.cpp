#include <stdlib.h>
#include <string>
#include <iostream>

#include "clipp.h"

#include "sin.h"
#include "wave.h"
#include "int2chars.h"

using namespace clipp;
using std::string;
using std::vector;

int main(int argc, char **argv)
{

    uint32_t duration = 10, base_freq = 440, sample_rate = 44100, bits_per_sample = 16;
    uint16_t num_channels = 1;
    vector<int> harmonic;
    string outfile;

    // 用clipp接收命令行参数
    auto cli = (value("outfile", outfile),
                option("-d", "--duration") & value("duration", duration) % "wave duration",
                option("-f", "--base_frequency") & value("frequency", base_freq) % "base frequency of the sound",
                option("-h", "--harmonic") & values("harmonic distribution", harmonic) % "harmonic distribution of the sound",
                option("-n", "--channel_number") & value("number", num_channels) % "number of channels",
                option("-s", "--sample_rate") & value("rate", sample_rate) % "sample rate",
                option("-b", "--sample_bits") & value("sample bits", bits_per_sample) % "bits per sample"
                );

    if (!parse(argc, argv, cli))
    {
        std::cout << make_man_page(cli, argv[0]);
        exit(-1);
    }

    //这两参数必须一致，不然会出错
    Wave wave(num_channels, sample_rate, bits_per_sample, duration);
    int data_len = 0;
    char *data_ptr = nullptr;
    sin(num_channels, sample_rate, bits_per_sample, duration, base_freq, harmonic, data_ptr, data_len);
    wave.writeFile(outfile, data_ptr, data_len);

    return 0;
}