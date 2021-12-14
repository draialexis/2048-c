#include "../include_b/toolbox_b.h"
#include "../include_b/game_b.h"


int main(int argc, char **argv) {

    srand(time(NULL));

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
            if (rdVal == 4) {
                rdVal = ((rand() % 2) + 1) * 2;//If it's a 4, we flip the coin again --> 25% chance
            }
            //spawn a tile, of val 2 or 4, somewhere on board
            SpawnTiles(g, rdVal, 1);
        }

        DisplayGame(g);

        if (g->free_tiles == 0) {
            CheckLose(g);
        }

        PromptMove(&isOn, &wasMove, g);
    }
    FreeGame(g);
    return EXIT_SUCCESS;
}
