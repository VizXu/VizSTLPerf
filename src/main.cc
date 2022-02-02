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
* 方法：<组件> <操作> [动作|方法] [POD|OBJ] [size] [looptimes]
*************************************************************/

void usage(void)
{
    std::cout<<"======================================welcome to use VizSTLPerf============================================\n";
    std::cout<<"Description:\n";
    std::cout<<"\tVizSTLPerf is a tool to measure the operations performance of STL components, such as the insert\n";
    std::cout<<"\tdelete, query, modify performance of List, Vector etc.\n";
    std::cout<<"Supports(container/algorithm):\n";
    std::cout<<"\tcontainer:\n";
    std::cout<<"\t\tarray\n";
    std::cout<<"\t\tstring\n";
    std::cout<<"\t\tlist\n";
    std::cout<<"\t\tforward_list\n";
    std::cout<<"\t\tvector\n";
    std::cout<<"\t\tdeque\n";
    std::cout<<"\t\tqueue\n";
    std::cout<<"\t\tpriority_queue\n";
    std::cout<<"\t\tmap\n";
    std::cout<<"\t\tset\n";
    std::cout<<"\t\ttuple\n";
    std::cout<<"\t\tunordered_map\n";
    std::cout<<"\t\tunordered_set\n";
    std::cout<<"\talgorithm:\n";
    std::cout<<"\t\tany_of\n";
    std::cout<<"\t\tall_of\n";
    std::cout<<"\t\tsort\n";
    std::cout<<"\t\tfind\n";
    std::cout<<"\t\tfind_n\n";
    std::cout<<"Usage Example:\n";
    std::cout<<"\tVizSTLPerf list --ops insert --action push_back --looptimes 1000\n";
    std::cout<<"==========================================================================================================="<<std::endl;
}

struct commands {
    const char *name;
    int (*function)(int argc, char *argv[]);
    void (*usage)(void);
    const char *help;
};

static const struct commands cmds[] = {
    {"list", listPerf, listPerfUsage, NULL},
    {NULL, NULL, NULL, NULL}
};

int run_command(const struct commands *cmd, int argc, char *argv[])
{
    // std::cout<<"run command, cmd->name is "<<cmd->name<<std::endl;
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
        usage();
    }
out:
    return (rc > -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}
