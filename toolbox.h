#ifndef INC_2048_C_TOOLBOX_H
#define INC_2048_C_TOOLBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//don't use DEBUG in replit...
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT printf("failing out\n");exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); FAIL_OUT

#endif //INC_2048_C_TOOLBOX_H
