#include <iostream>
#include <tuple>
#include <syslog.h>
#include <getopt.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "ListPerf.h"

/************************************************************
* 功能：该程序用以测度STL各组件各种操作的性能
* 支持：支持常用的STL组件，如vector, list, deque, map, set等
* 方法：<组件> <操作> [动作|方法] [size] [looptimes]
*************************************************************/

void usage(void)
{
    std::cout<<"=============welcome to use VizSTLPerf=============\n";
    std::cout<<"Description:\n";
    std::cout<<"\tVizSTLPerf is a tool to measure the operations\n";
    std::cout<<"\tperformance of STL components, such as the insert\n";
    std::cout<<"\tperformance of List, Vector etc.\n";
    std::cout<<"Supports:\n";
    std::cout<<"==================================================="<<std::endl;
}

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

int run_command(const struct commands *cmd, int argc, char *argv[])
{
    return cmd->function(argc, argv);
}

int main(int argc, char *argv[])
{
    static const struct option opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"debug", no_argument, NULL, 'd'},
        {NULL, 0, NULL, 0}
    };
    char *cmd = nullptr;
    int opt;
    int i, rc = -1;
    bool debug = false;
    for (;;) {
        opt = getopt_long(argc, argv, "+dh", opts, NULL);
        if (opt == -1) {
            break;
        }
        switch (opt) {
            case 'h':
                usage();
                goto out;
            case 'd':
                debug = true;
            case '?':
                usage();
                goto out;
            default:
                usage();
                goto out;
        }
    }
    cmd = argv[optind];
    if (cmd) {
        for (i = 0; cmds[i].name != NULL; i++) {
            if (!strncmp(cmds[i].name, cmd, strlen(cmds[i].name))) {
                argc -= optind;
                argv += optind;
                optind = 0;
                rc = run_command(&cmds[i], argc, argv);
                goto out;
            }
        }
    }
out:
    return (rc > -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}
