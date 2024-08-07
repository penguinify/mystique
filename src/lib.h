#ifndef LIB_H
#define LIB_H

struct Video {
    char title[50];
    char artist[50];
    char album[50];
    int state;
};

int classify(struct Video video);

struct Video get_current_video();

int start_daemon();
int stop_daemon();

int repair_daemon();

#endif //LIB_H
