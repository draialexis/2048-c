#include "toolbox.h"

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
