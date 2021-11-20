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

    uint32_t duration = 10, base_freq = 440;
    vector<int> harmonic;
    string outfile;

    // 用clipp接收命令行参数
    auto cli = (value("outfile", outfile),
                option("-d", "--duration") & value("duration", duration) % "wave duration",
                option("-f", "--base_frequency") & value("frequency", base_freq) % "base frequency of the sound",
                option("-h", "--harmonic") & values("harmonic distribution", harmonic) %
                                                 "harmonic distribution of the sound");

    if (!parse(argc, argv, cli))
    {
        std::cout << make_man_page(cli, argv[0]);
        exit(-1);
    }

    //这两参数必须一致，不然会出错
    Wave wave(1, 44100, 16, duration);
    int data_len = 0;
    char *data_ptr = nullptr;
    sin(1, 44100, 16, duration, base_freq, harmonic, &data_ptr, &data_len);
    wave.writeFile(outfile, data_ptr, data_len);

    return 0;
}