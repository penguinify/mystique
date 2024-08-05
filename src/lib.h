#ifndef LIB_H
#define LIB_H

struct Video {
    char title[50];
    char artist[50];
};

int classify(char *title, char *artist);

struct Video get_current_video();

#endif //LIB_H
