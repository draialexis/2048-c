#ifndef INC_2048_C_TOOLBOX_H
#define INC_2048_C_TOOLBOX_H

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT DEBUG exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("_____ MALLOC FAILED _____\n"); FAIL_OUT

#define N 4

#endif //INC_2048_C_TOOLBOX_H
