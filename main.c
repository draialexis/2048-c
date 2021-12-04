#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));
    Game *gPtr = MakeGame();
    int hasMoved = 0;  // pseudo-booleans: has the player won?has the player successfully moved?
    int isOn = Menu(gPtr); // pseudo-boolean: is the game on?
    int rdVal; // a random value to be used for tile spawning

    int first = 1; // round 1?

    while (isOn) {
        if (first){
            first = 0;
        } else {
            //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
            rdVal = ((rand() % 2) + 1) * 2;
            SpawnTiles(gPtr, rdVal, 1);
        }

        DisplayGame(gPtr);

        if (gPtr->freeTiles == 0) {
            CheckLose(gPtr);
        }

        hasMoved = PromptMove(&isOn, gPtr);
        while (!hasMoved) {
            printf("ce mouvement est impossible\n");
            hasMoved = PromptMove(&isOn, gPtr);
        }
    }

    return 0;
}
