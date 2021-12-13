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
 * performs the tasks of TTF_RenderText_Blended(), with error checking included
 * @param fnt a pointer to a TTF_Font
 * @param txt a string
 * @param clr an SDL_Color
 * @return
 */
SDL_Surface *MyRenderText(TTF_Font *fnt, const char *txt, SDL_Color clr);

/**
 * performs the tasks of SDL_BlitSurface(), with error checking included
 * @param src a pointer to a source SDL_Surface
 * @param srcrect a pointer to a portion of said source
 * @param dst a pointer to a destination SDL_Surface
 * @param pos a pointer to a SDL_Rect containing position information
 */
void MyBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *pos);

/**
 * performs the tasks of SDL_Flip(), with error checking included
 * @param screen a pointer to the SDL_Surface to refresh
 */
void MyFlip(SDL_Surface *screen);

/**
 * performs the tasks of SDL_WaitEvent(), with error checking included
 * @param evt a pointer to an SDL_Event to wait on
 */
void MyWait(SDL_Event *evt);

#endif //INC_2048_C_TOOLBOX_H
