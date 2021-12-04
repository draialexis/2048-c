#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));

    Game *gPtr = MakeGame();
    int isOn = Menu(gPtr); // pseudo-boolean: is the game on?
    int rdVal; // a random value to be used for tile spawning
    int isFirst = 1; // round 1?

    while (isOn) {
        if (isFirst) {
            isFirst = 0;
        } else {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = ((rand() % 2) + 1) * 2;
            //spawn a tile, of val 2 or 4, somewhere on the board
            SpawnTiles(gPtr, rdVal, 1);
        }

        DisplayGame(gPtr);

        if (gPtr->freeTiles == 0) {
            CheckLose(gPtr);
        }

        PromptMove(&isOn, gPtr);
    }
    return 0;
}
