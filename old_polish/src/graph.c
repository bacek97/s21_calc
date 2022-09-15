
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "visual.h"
#include "input.h"
#include "yard.h"

int main() {
    char *s = (char *) malloc(128 * sizeof(char));
    CHECKMALLOC(s);
    scanf("%128s", s);
    char* ss = truncate_trig(s);  //  contains 'x'
    char *sss = str_replace(ss, "x", "%lf");
    Clear();
    Goto(0, 0);
    fillDots();
    for (double x_count = 0; x_count < 4 * M_PI; x_count += 4 * M_PI / 80) {
        char *str = format_x(sss, x_count);
        double y_count = yard(str);
        double x = x_count * 100 / 15;
        double y = 13 + y_count * 10;
        x = round(x);
        y = round(y);
//        printf("%lf %lf\n",x,y);
        Goto((int) x, (int) y);
        print();
        free(str);
    }
    free(sss);
    free(ss);
    free(s);
    Goto(85, 30);
    getchar();
    return 0;
}
