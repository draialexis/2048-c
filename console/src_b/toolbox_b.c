//// Walid EL CHEIK, Alexis DRAI, 17/12/2021

#include "../include_b/toolbox_b.h"

int GetInput() {
    int res = getchar();
    int dump;
    while ((dump = getchar()) != '\n' && dump != EOF) {
        //do nothing
    }
    return res;
}

int isFOpen(FILE *f, char *f_name) {
    if (f == NULL) {
        printf("error while opening file '%s'\n", f_name);
        return 0;
    }
    return 1;
}
