#include "toolbox.h"

void Purge() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void CheckFOpen(FILE *f, char *f_name) {
    if (f == NULL) {
        printf("error while opening file '%s'\n", f_name);
        FAIL_OUT
    }
}
