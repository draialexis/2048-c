#ifndef INC_2048_C_TOOLBOX_H
#define INC_2048_C_TOOLBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//don't use DEBUG in replit...
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT printf("failing out\n");DEBUG exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); FAIL_OUT

/**
 * empties stdin from all superfluous characters, including final \\n
 */
void Purge();

/**
 * checks if a file was open successfully; exits with error if not
 * @param f a pointer to the FILE
 * @param f_name the name of the file
 */
void CheckFOpen(FILE *f, char *f_name);


#endif //INC_2048_C_TOOLBOX_H
