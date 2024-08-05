#include <stdio.h>
#include <stdlib.h>

#include "lib.h"



int main() {
    
    struct Video video = get_current_video();

    int type = classify(video.title, video.artist);
    printf("%d\n", type);

    if (type == 3) {
        system("nowplaying-cli seek 1000");
    }

    return 0;
}
