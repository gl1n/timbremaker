#include <stdlib.h>
#include <string>
#include <iostream>

#include "clipp.h"

#include "sin.h"
#include "wave.h"
#include "int2chars.h"

using namespace clipp;
using std::string;

int main(int argc, char **argv)
{
    uint32_t duration = 10, base_freq = 440;
    double second_w = 0, third_w = 0;
    string outfile = "default.wav";

    auto cli = (value("outfile", outfile).doc("output file name"),
                option("-d", "--duration") & value("duration", duration),
                option("-f", "--base_frequency") & value("frequency", base_freq)
                // option("")
    );

    if (!parse(argc, argv, cli))
        std::cout << make_man_page(cli, argv[0]);

    //这两参数必须一致，不然会出错
    Wave wave(1, 44100, 16, duration);
    int data_len = 0;
    char *data_ptr = nullptr;
    sin(1, 44100, 16, duration, base_freq, second_w, third_w, &data_ptr, &data_len);
    wave.writeFile(outfile, data_ptr, data_len);

    return 0;
}