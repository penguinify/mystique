#include <stdio.h>
#include <string.h>

#include "lib.h"


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
        printf("Failed to run command\n");
        return 1;
    }

    fgets(type, 14, output);

    if (strcmp(type, "song") == 0) {
        return 2;
    } else if (strcmp(type, "advertisement") == 0) {
        return 3;
    } else {
        return 1;
    }
}

struct Video get_current_video() {
    FILE *output;
    char title[50], artist[50];

    output = popen("nowplaying-cli get title artist", "r");

    if (output == NULL)
        return (struct Video) { "", "" };

    fgets(title, 50, output);
    fgets(artist, 50, output);

    return (struct Video) { *title, *artist };
}
