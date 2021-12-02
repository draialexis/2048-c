#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));
    Game *gPtr = MakeGame();
    int hasMoved = 0;  // pseudo-booleans: has the player won?has the player successfully moved?
    int isOn = Menu(gPtr); // pseudo-boolean: is the game on?
    int rdVal; // a random value to be used for tile spawning

    while (isOn) {
        DisplayGame(gPtr);

        if (gPtr->freeTiles == 0) {
            printf("if no possible merge, game over (to be implemented)\n");
        }

        hasMoved = PromptMove(&isOn, gPtr);
        while (!hasMoved) {
            hasMoved = PromptMove(&isOn, gPtr);
        }

        //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
        rdVal = ((rand() % 2) + 1) * 2;
        SpawnTiles(gPtr, rdVal, 1);
    }

    return 0;
}
