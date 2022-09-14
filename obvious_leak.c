#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    while (1) {
        char* a = malloc(1);
        free(a);
        sleep(1);
        puts("malloc");
    }
    return 0;
}