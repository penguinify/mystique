#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "lib.h"
#include "conf.h"


/* 1. ERR
 * 2. SONG
 * 3. ADVERTISEMENT
 */
int classify(char *title, char *artist) {
    FILE *output;
    char type[15];

    char command[130];
    sprintf(command, "python3 ./src/ml/classify.py \"%s\" \"%s\"", title, artist);

    output = popen(command, "r");
    if (output == NULL) {
        pclose(output);

        printf("Failed to run command\n");
        return 1;
    }

    fgets(type, 14, output);

    pclose(output);

    if (strcmp(type, "song\n") == 0) {
        return 2;
    } else if (strcmp(type, "advertisement") == 0) {
        return 3;
    } else {
        return 1;
    }
}

struct Video get_current_video() {
    FILE *output;
    
    struct Video video = { "", "" };

    output = popen("nowplaying-cli get title artist", "r");

    if (output == NULL) {
        pclose(output);
        return video;
    }

    fgets(video.title, 50, output);
    fgets(video.artist, 50, output);

    pclose(output);
    
    // Remove newline characters
    
    video.title[strcspn(video.title, "\n")] = 0;
    video.artist[strcspn(video.artist, "\n")] = 0;

    return video;
}

int start_daemon() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid > 0) {
        return 0;
    }

    // save procid to file
    // line 1: THIS FILE IS GENERATED BY MYSTIQUE, IT CONTAINS INFORMATION ABOUT THE CURRENTLY RUNNING DAEMON. DO NOT EDIT ANY VALUES UNLESS YOU KNOW WHAT YOU ARE DOING!
    // line 2: <version>
    // line 3: <pid>
    // line 4: <state> 
    // 1 = running
    // 0 = stopped
    FILE *file = fopen("daemon.txt", "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    fprintf(file, "THIS FILE IS GENERATED BY MYSTIQUE, IT CONTAINS INFORMATION ABOUT THE CURRENTLY RUNNING DAEMON. DO NOT EDIT ANY VALUES UNLESS YOU KNOW WHAT YOU ARE DOING!\n");
    fprintf(file, "%s\n", VERSION);
    fprintf(file, "%d\n", getpid());
    fprintf(file, "1\n");

    fclose(file);

    while (1) {
        struct Video video = get_current_video();

        int type = classify(video.title, video.artist);

        if (type == 3) {
            system("nowplaying-cli seek 1000");
        }

        sleep(4);
    }
}

int stop_daemon() {
    FILE *file = fopen("daemon.txt", "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    char version[10];
    int pid;
    int state;

    // skips first line
    char c;
    while ((c = fgetc(file)) != '\n');

    fgets(version, 10, file);
    fscanf(file, "%d", &pid);
    fscanf(file, "%d", &state);

    fclose(file);

    if (state == 0) {
        printf("Daemon is already stopped\n");
        return 0;
    }

    kill(pid, SIGKILL);

    file = fopen("daemon.txt", "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    fprintf(file, "THIS FILE IS GENERATED BY MYSTIQUE, IT CONTAINS INFORMATION ABOUT THE CURRENTLY RUNNING DAEMON. DO NOT EDIT ANY VALUES UNLESS YOU KNOW WHAT YOU ARE DOING!\n");
    fprintf(file, "%s\n", version);
    fprintf(file, "%d\n", pid);
    fprintf(file, "0\n");

    fclose(file);

    return 0;
}
