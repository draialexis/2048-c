#include <SDL.h>
#include <SDL_ttf.h>
#include "../include/SDL.h"//<<<<TODO remove #include before shipping
#include "../include/SDL_ttf.h"//<<<<TODO remove HEADER FILE before shipping
#include "../include/toolbox.h"
#include "../include/game.h"

int main(int argc, char **argv) {

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        fprintf(stderr, "\nUnable to initialize TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Surface *screen = NULL;

    screen = SDL_SetVideoMode(WID, HEI, BPP, SDL_HWSURFACE);//DOUBLEBUF?

    if (screen == NULL) {
        fprintf(stderr, "\nVideoMode error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("2048", NULL);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 250, 250, 250));

    Game *g = MakeGame(); // pointer to game

    char *fntPath = "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf";
    TTF_Font *fnt = NULL;
    fnt = TTF_OpenFont(fntPath, 24);
    if (fnt == NULL) {
        fprintf(stderr, "\nUnable to load TTF font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    int isOn = Menu(g, screen, fnt); // boolean: is game on?
    int wasMove = 0; // boolean: was the last action actually a move?
    int rdVal; // a random value to be used for tile spawning
    int isFirst = 1; // boolean: is it round 1?

    while (isOn) {
        if (isFirst) {
            isFirst = 0;
        } else if (wasMove) {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = ((rand() % 2) + 1) * 2;
            //spawn a tile, of val 2 or 4, somewhere on board
            SpawnTiles(g, rdVal, 1);
        }

        DisplayGame(g, screen, fnt);

        if (g->free_tiles == 0) {
            CheckLose(g);
        }

        PromptMove(&isOn, &wasMove, g, fnt);
    }

    SDL_FreeSurface(screen);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
