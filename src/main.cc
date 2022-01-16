#include <iostream>
#include <tuple>
#include <syslog.h>
#include <getopt.h>
#include <unistd.h>
#include "ListPerf.h"

/************************************************************
* 功能：该程序用以测度STL各组件各种操作的性能
* 支持：支持常用的STL组件，如vector, list, deque, map, set等
* 方法：<组件> <操作> [动作|方法] [size] [looptimes]
*************************************************************/

struct commands {
    const char *name;
    int (*function)(int argc, char *argv[]);
    void (*usage)(void);
    const char *help;
};

static const struct commands cmds[] = {
    {"List", listPerf, listPerfUsage, NULL},
    {NULL, NULL, NULL, NULL}
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout<<"parameter not correct!"<<std::endl;
        return -1;
    }
    std::cout<<"hello, welcome use "<<std::string(argv[0]).erase(0, 2)<<"..."<<std::endl;
    // listIntergerPerf(1000000, 1);
    return 0;
}
