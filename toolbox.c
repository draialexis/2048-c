#include "toolbox.h"

void Purge() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
