#include "../include/toolbox.h"
#include "../include/game.h"

int main(int argc, char **argv) {//not used, but important for SDL
    start_game:;
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        DEBUG
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() != 0) {
        DEBUG
        fprintf(stderr, "\nUnable to initialize TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    Game *g = MakeGame(); // pointer to game

    g->isOn = Menu(g);
    int rdVal; // a random value to be used for tile spawning
    int isFirst = 1; // boolean: is it round 1?

    Uint32 current_time;
    Uint32 prev_time = 0;
    char time_str[32] = "";
    SDL_Surface *counter_dis = NULL;
    SDL_Rect pos;

    while (g->isOn) {
        if (isFirst) {
            isFirst = 0;
        } else if (g->wasMove) {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = ((rand() % 2) + 1) * 2;
            if (rdVal == 4) {
                rdVal = ((rand() % 2) + 1) * 2;//If it's a 4, we flip the coin again --> 25% chance
            }
            //spawn a tile, of val 2 or 4, somewhere on board
            SpawnTiles(g, rdVal, 1);
        }

        SDL_FreeSurface(g->screen);
        if (SDL_FillRect(g->screen, NULL, SDL_MapRGB(g->screen->format, 230, 230, 230)) != 0) {
            DEBUG
            fprintf(stderr, "\nUnable to initialize screen: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        current_time = SDL_GetTicks();
        if (current_time - prev_time >= 1000) {
            g->seconds += 1;
            sprintf(time_str, "secondes : %d", g->seconds);
            SDL_FreeSurface(counter_dis);
            counter_dis = TTF_RenderText_Blended(g->fnt, time_str, g->fnt_clr);//time counter display
            if (counter_dis == NULL) {
                DEBUG
                fprintf(stderr, "\nTTF RenderText error: %s\n", TTF_GetError());
                exit(EXIT_FAILURE);
            }
            prev_time = current_time;
        }
        pos.x = PAD;
        pos.y = PAD + (H_T * 2);//3rd line
        if (SDL_BlitSurface(counter_dis, NULL, g->screen, &pos) != 0) {
            DEBUG
            fprintf(stderr, "\nUnable to initialize counter: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        DisplayGame(g);

        g->status = CheckStatus(g);
        if (g->status != 0) {
            if (EndGame(g)) {
                goto start_game;
            }
        }

        PromptMove(g);
    }
    FreeGame(g);
    return EXIT_SUCCESS;
}
