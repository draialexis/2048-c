//// Walid EL CHEIK, Alexis DRAI, 17/12/2021

#include "../include/toolbox.h"
#include "../include/game.h"

int main(int argc, char **argv) {//not used, but important for SDL
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //ignore any mouse events, to avoid processing one event per micro-motion...
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    if (TTF_Init() != 0) {
        fprintf(stderr, "\nUnable to initialize TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    start_game:;
    Game *g = MakeGame(); // pointer to game
    g->isOn = Menu(g);
    unsigned short int rdVal; // a random value to be used for tile spawning
    int isFirst = 1; // boolean: is it round 1?
    Uint32 prv_time;

    while (g->isOn) {
        prv_time = SDL_GetTicks();//time spent since SDL_Init()
        if (isFirst) {
            isFirst = 0;
        } else if (g->wasMove) {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = (unsigned short int) ((rand() % 2) + 1) * 2;
            if (rdVal == 4) {
                rdVal = (unsigned short int) ((rand() % 2) + 1) * 2;//If it's a 4, we flip the coin again --> 25% chance
            }
            //spawn a tile, of val 2 or 4, somewhere on board
            SpawnTiles(g, rdVal, 1);
        }
        //print out the game state
        DisplayGame(g);
        //if board full, see if game over
        if (g->free_tiles == 0) { CheckLose(g); }
        //if win or lose, send to end game
        if (g->status != 0) {
            //if player chooses to restart, go back to start
            if (EndGame(g)) { goto start_game; }
        }
        //ask the player to make a move
        PromptMove(g);
        Uint32 spent = SDL_GetTicks() - prv_time;//time spent in this iteration
        if (spent < ITV) {
            SDL_Delay(ITV - spent);
            g->msecs += ITV;
        } else { g->msecs += spent; }
    }
    FreeGame(g);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
