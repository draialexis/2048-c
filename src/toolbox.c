#include "../include/toolbox.h"

int isFOpen(FILE *f, char *f_name) {
    if (f == NULL) {
        fprintf(stderr, "error while opening file '%s'\n", f_name);
        return 0;
    }
    return 1;
}

void MyFillRect(SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color) {
    if (SDL_FillRect(dst, dstrect, color) != 0) {
        fprintf(stderr, "\nSDL_FillRect error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

SDL_Surface *MyRenderText(TTF_Font *fnt, const char *txt, SDL_Color clr) {
    SDL_Surface *res = NULL;
    res = TTF_RenderText_Blended(fnt, txt, clr);
    if (res == NULL) {
        fprintf(stderr, "\nTTF_RenderText error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return res;
}

void MyBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *pos) {
    if (SDL_BlitSurface(src, srcrect, dst, pos) != 0) {
        fprintf(stderr, "\nSDL_BlitSurface error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void MyFlip(SDL_Surface *screen) {
    if (SDL_Flip(screen) != 0) {
        fprintf(stderr, "\nSDL_Flip error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void MyWait(SDL_Event *evt) {
    if (!SDL_WaitEvent(evt)) {
        fprintf(stderr, "\nUnable to wait for event: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}