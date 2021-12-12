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

    Game *g = MakeGame(); // pointer to game

    SDL_Surface *screen_ = NULL;
    screen_ = SDL_SetVideoMode(WID, HEI, BPP, SDL_HWSURFACE);
    if (screen_ == NULL) {
        fprintf(stderr, "\nVideoMode error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FillRect(screen_, NULL, SDL_MapRGB(screen_->format, 230, 230, 230));
    SDL_WM_SetCaption("2048", NULL);
    g->screen = screen_;

    char *fntPath = "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf";
    TTF_Font *fnt_ = NULL;
    fnt_ = TTF_OpenFont(fntPath, 24);
    if (fnt_ == NULL) {
        fprintf(stderr, "\nUnable to load TTF font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    g->fnt = fnt_;

    int isOn = Menu(g); // boolean: is game on?
    int wasMove = 0; // boolean: was the last action actually a move?
    int rdVal; // a random value to be used for tile spawning
    int isFirst = 1; // boolean: is it round 1?

    SDL_Color charcoal = {33, 33, 33};
    Uint32 current_time = 0, prev_time = 0;
    int second = 1000;
    char time_str[32] = "";
    SDL_Surface *counter_dis = TTF_RenderText_Solid(g->fnt, time_str, charcoal);//time counter display
    SDL_Rect pos;

    while (isOn) {
        if (isFirst) {
            isFirst = 0;
        } else if (wasMove) {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = ((rand() % 2) + 1) * 2;
            //spawn a tile, of val 2 or 4, somewhere on board
            SpawnTiles(g, rdVal, 1);
        }

        SDL_FreeSurface(g->screen);
        SDL_FillRect(g->screen, NULL, SDL_MapRGB(g->screen->format, 230, 230, 230));

        current_time = SDL_GetTicks();
        if (current_time - prev_time >= second) {
            g->seconds += second;
            sprintf(time_str, "secondes : %d", g->seconds / 1000);
            SDL_FreeSurface(counter_dis);
            counter_dis = TTF_RenderText_Blended(g->fnt, time_str, charcoal);
            prev_time = current_time;
        }
        pos.x = PAD;
        pos.y = PAD + (H_T * 2);//3rd line
        SDL_BlitSurface(counter_dis, NULL, g->screen, &pos);

        DisplayGame(g);

        if (g->free_tiles == 0) {
            CheckLose(g);
        }

        PromptMove(&isOn, &wasMove, g);
    }

    FreeGame(g);
    return EXIT_SUCCESS;
}
