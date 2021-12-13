#ifndef INC_2048_C_TOOLBOX_H
#define INC_2048_C_TOOLBOX_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG fprintf(stderr, "file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT fprintf(stderr, "failing out\n");DEBUG exit(EXIT_FAILURE);
#define MALLOC_FAIL fprintf(stderr, "!_malloc failed_!\n"); FAIL_OUT

/**
 * checks if a file was open successfully; exits with error if not
 * @param f a pointer to the FILE
 * @param f_name the name of the file
 * @return if file was able to be opened, 1; else, 0
 */
int isFOpen(FILE *f, char *f_name);

/**
 * performs the tasks of SDL_FillRect(), with error checking included
 * @param dst a pointer to an SDL_Surface
 * @param dstrect a pointer to an SDL_Rect, the area of dst that will be filled
 * @param color a Uint32 color, ideally built with SDL_MapRGB()
 */
void MyFillRect(SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color);

/**
 *
 * @param fnt
 * @param txt
 * @param clr
 * @return
 */
SDL_Surface *MyRenderText(TTF_Font *fnt, const char *txt, SDL_Color clr);

/**
 *
 * @param src
 * @param srcrect
 * @param dst
 * @param pos
 */
void MyBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *pos);

/**
 *
 * @param screen
 */
void MyFlip(SDL_Surface *screen);

/**
 *
 * @param evt
 */
void MyWait(SDL_Event *evt);

#endif //INC_2048_C_TOOLBOX_H
