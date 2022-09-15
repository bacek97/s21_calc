//
// Created by Gladis Ariane on 4/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "visual.h"

// Заполняем 80х25 точками
void fillDots() {
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            printf("%c", '.');
        }
        printf("\n");
    }
}

// Используем ESC-символытерминала чтобы перейти в нужный Х и Y
void Goto(int x, int y) {
    char *fo;
    asprintf(&fo, "\033[%d;%dH", y, x);
    printf("%s", fo);
    free(fo);
}

void Clear() {
    printf("\033[2J");
}

void print() {
    printf("*");
}
