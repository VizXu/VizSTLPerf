#include <iostream>
#include <list>
#include <chrono>
#include <climits>
#include <getopt.h>
#include <unistd.h>
#include "Common.h"
#include "RandomGenerator.h"

inline std::string podType2String(enum PerfPODType type) {
    std::vector<std::string> types{"pod_of_char", "pod_of_int", "pod_of_long", "pod_of_float", "pod_of_double"};
    return types[type];
}

int listPushBackPODPerf(enum PerfPODType type, uint32_t size, uint32_t looptimes)
{
    // RandomGenerator<int> vrg(size, INT_MIN, INT_MAX);
    std::list<char> lchar;
    std::list<int> lint;
    std::list<long> llong;
    std::list<float> lfloat;
    std::list<double> ldouble;
    auto start = std::chrono::steady_clock::now();
    switch (type) {
        case PODCHAR:
        {
            for (uint32_t i = 0u; i < looptimes; i++) {
                for (uint32_t j = 0u; j < size; j++) {
                    lchar.push_back(j);
                }
            }
        }   break;
        case PODINT:
        {
            for (uint32_t i = 0u; i < looptimes; i++) {
                for (uint32_t j = 0u; j < size; j++) {
                    lint.push_back(j);
                }
            }
        }   break;
        case PODLONG:
        {
            for (uint32_t i = 0u; i < looptimes; i++) {
                for (uint32_t j = 0u; j < size; j++) {
                    llong.push_back(j);
                }
            }
        }   break;
        case PODFLOAT:
        {
            for (uint32_t i = 0u; i < looptimes; i++) {
                for (uint32_t j = 0u; j < size; j++) {
                    lfloat.push_back(j);
                }
            }
        }   break;
        case PODDOUBLE:
        {
            for (uint32_t i = 0u; i < looptimes; i++) {
                for (uint32_t j = 0u; j < size; j++) {
                    ldouble.push_back(j);
                }
            }
        }   break;
        default:
            break;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout<<"Perf: list push_back "<<podType2String(type)<<" for "<<size<<" counts of item and "<<looptimes<<" times, takes "<<diff.count()/(double)looptimes<<"s"<<std::endl;
    return 0;
}

int listEmplaceBackPODPerf(uint32_t size, uint32_t looptimes)
{
    std::list<int> l;
    auto start = std::chrono::steady_clock::now();
    for (uint32_t i = 0u; i < looptimes; i++) {
        for (uint32_t j = 0u; j < size; j++) {
            l.emplace_back(j);
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout<<"Perf: list emplace_back interger for "<<size<<" counts of item and "<<looptimes<<" times, takes "<<diff.count()/(double)looptimes<<"s"<<std::endl;
    return 0;
}

void listPerfUsage(void)
{
    std::cout<<"=======================================list perf test==========================================\n";
    std::cout<<"STL List Perf Testing..."<<std::endl;
    std::cout<<"Parameters:\n";
    std::cout<<"\t--ops <insert|delete|query|modify>\n";
    std::cout<<"\t--action <push_back|push_front|>\n";
    std::cout<<"\t--object <pod|obj|customize>\n";
    std::cout<<"\t--size size\n";
    std::cout<<"\t--looptimes looptimes\n";
    std::cout<<"===============================================================================================\n";
}

int listPerf(int argc, char *argv[])
{
    static const struct option opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"action", required_argument, NULL, 'a'},
        {"object", required_argument, NULL, 'o'},
        {"size", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0},
    };
    int rc = -1, i;
    char *cmd = NULL;
    int opt;
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
    if (rc == -1) {
        listPerfUsage();
    }
    return (rc == -1) ? EXIT_FAILURE : EXIT_SUCCESS;
}

