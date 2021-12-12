#include "toolbox.h"

int isFOpen(FILE *f, char *f_name) {
    if (f == NULL) {
        printf("error while opening file '%s'\n", f_name);
        return 0;
    }
    return 1;
}
