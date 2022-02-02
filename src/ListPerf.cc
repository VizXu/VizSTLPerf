#include <iostream>
#include <list>
#include <chrono>
#include <climits>
#include <getopt.h>
#include <unistd.h>
#include "RandomGenerator.h"

int listIntergerPerf(uint32_t size, uint32_t looptimes)
{
    (void)size;
    (void)looptimes;
    RandomGenerator<int> vrg(size, INT_MIN, INT_MAX);
    std::vector<int> v = vrg.getRandoms();
    std::list<int> l;
    auto start = std::chrono::steady_clock::now();
    for (uint32_t i = 0u; i < size; i++) {
        l.push_back(v[i]);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout<<"Perf: list push_back interger for "<<size<<" times, takes "<<diff.count()<<"s"<<std::endl;
    return 0;
}

void listPerfUsage(void)
{
    std::cout<<"STL List Perf Testing..."<<std::endl;
}

int listPerf(int argc, char *argv[])
{
    static const struct option opts[] = {
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0},
    };
    int rc = -1, i;
    char *cmd = NULL;
    int opt;
    std::cout<<"start listPerf...."<<std::endl;
    for (;;) {
        opt = getopt_long(argc, argv, "h", opts, NULL);
        if (opt == -1) {
            break;
        }
        switch (opt) {
            case 'h':
                listPerfUsage();
                break;
            case '?':
                break;
            default:
                break;
        }
    }
out:
    return (rc == -1) ? EXIT_FAILURE : EXIT_SUCCESS;
}

