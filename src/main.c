#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <getopt.h>

#include "lib.h"
#include "conf.h"


void print_help() {
    printf("Usage: %s [OPTION]\n", "main");
    printf("  -h, --help\t\tPrint this help message\n");
    printf("  -v, --version\t\tPrint the version\n");
    printf("  --start-daemon\tStart the daemon\n");
    printf("  --stop-daemon\t\tStop the daemon\n");
}

void print_version() {
    printf("Version: %s\n", VERSION);

    FILE *output = popen("python3 --version", "r");
    if (output == NULL) {
        printf("Python3 is NOT installed. Please install it.\n");
    } else {
        printf("Python3 is installed.\n");
    }

    pclose(output);
}

void parse_args(int argc, char *argv[]) {

    if (argc == 1) {
        print_help();
        return;
    }

    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"start-daemon", no_argument, 0, 1},
        {"stop-daemon", no_argument, 0, 2},
        {0, 0, 0, 0}
    };

    int c;
    int option_index = 0;

    while ((c = getopt_long(argc, argv, "hv", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                print_help();
                return;
            case 'v':
                print_version();
                return;
            case 1:
                printf("Starting daemon\n");
                start_daemon();
                printf("Daemon started\n");
                return;
            case 2:
                printf("Stopping daemon\n");
                stop_daemon();
                printf("Daemon stopped\n");
                return;
            default:
                print_help();
                return;
        }
    }
}


int main(int argc, char *argv[]) {
    
    // pid_t pid = fork();
    // if (pid == -1) {
    //     perror("fork");
    //     exit(1);
    // }
    //
    // printf("PID: %d\n", pid);
    //
    // // close parent
    // if (pid > 0) {
    //     return 0;
    // }

    // while (1)
    // {
    //     struct Video video = get_current_video();
    //
    //     int type = classify(video.title, video.artist);
    //     printf("%d\n", type);
    //
    //     if (type == 3) {
    //         system("nowplaying-cli seek 1000");
    //     }
    //
    //     sleep(4);
    // }
    
    parse_args(argc, argv);

    return 0;
}
