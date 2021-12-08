#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "../include/SDL.h"//<<<<TODO remove before shipping
#include "../include/toolbox.h"
#include "../include/game.h"

int main(int argc, char **argv) {

    srand(time(NULL));

    /*SDL_Surface *screen = NULL;
    SDL_Surface *rect = NULL;
    SDL_Rect pos;*/

    /*if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
*/
    /*if ((screen = SDL_SetVideoMode(W, H, BPP, SDL_HWSURFACE)) == NULL) {
        fprintf(stderr, "\nVideoMode error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }*/

    Game *g = MakeGame(); // pointer to game
    int isOn = Menu(g); // boolean: is game on?
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

        DisplayGame(g);

        if (g->free_tiles == 0) {
            CheckLose(g);
        }

        PromptMove(&isOn, &wasMove, g);
    }

    /*SDL_FreeSurface(screen);
    SDL_Quit();*/

    return EXIT_SUCCESS;
}
