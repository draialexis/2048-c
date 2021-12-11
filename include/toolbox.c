#include "toolbox.h"

void Purge() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
//TODO improve purge
int isFOpen(FILE *f, char *f_name) {
    if (f == NULL) {
        printf("error while opening file '%s'\n", f_name);
        return 0;
    }
    return 1;
}
