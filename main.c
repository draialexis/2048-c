#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));

    Game *g = MakeGame(); // pointer to game
    int isOn = Menu(g); // boolean: is game on?
    int rdVal; // a random value to be used for tile spawning
    int isFirst = 1; // boolean: is it round 1?

    while (isOn) {
        if (isFirst) {
            isFirst = 0;
        } else {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = ((rand() % 2) + 1) * 2;
            //spawn a tile, of val 2 or 4, somewhere on board
            SpawnTiles(g, rdVal, 1);
        }

        DisplayGame(g);

        if (g->free_tiles == 0) {
            CheckLose(g);
        }

        PromptMove(&isOn, g);
    }
    return 0;
}
