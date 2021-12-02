#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));
    Game * gPtr = MakeGame();
    int hasWon = 0, hasMoved = 0;  // pseudo-booleans: has the player won?has the player successfully moved?
    int isOn = Menu(gPtr); // pseudo-boolean: is the game on?
    int rdVal; // a random value to be used for tile spawning
    while (isOn) {
        DisplayGame(gPtr);

        if(gPtr->freeTiles == 0){
            printf("if no possible merge, game over (to be implemented)\n");
        }

        hasMoved = PromptMove(&isOn, gPtr);
        while(!hasMoved){
            hasMoved = PromptMove(&isOn, gPtr);
        }
        rdVal = ((rand() % 2) + 1) * 2 ;
        //rdm int value 'between 0+1 and 1+1' *2, so 'either 1 or 2' *2, so: 'either 2 or 4'
        SpawnTiles(gPtr, rdVal, 1);
        //board-moving goes here
        // on every merge instance
        //... counting score...
        // scoreUp = b[_][_]<<1;
        // b[_][_] = scoreUp;
        // score += scoreUp;
        // if(scoreUp == 2048) hasWon = 1;
        //... after counting all the merge score_ups ...

//        if (hasWon) {
//            hasWon = 0; //we've taken the win into account, we can reinit this to 0 for next game
//            isOn = YouWin(board, score);
//        }
    }
    return 0;
}
