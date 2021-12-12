#ifndef INC_2048_C_TOOLBOX_H
#define INC_2048_C_TOOLBOX_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT printf("failing out\n");DEBUG exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); FAIL_OUT

/**
 * checks if a file was open successfully; exits with error if not
 * @param f a pointer to the FILE
 * @param f_name the name of the file
 * @return if file was able to be opened, 1; else, 0
 */
int isFOpen(FILE *f, char *f_name);

#endif //INC_2048_C_TOOLBOX_H
