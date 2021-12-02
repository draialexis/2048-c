#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));
    Game * gPtr = MakeGame();
    Game g = *gPtr;
    int hasWon = 0, hasMoved = 0;  // pseudo-booleans: has the player won?has the player successfully moved ?
    //TODO do the pointer thingy with spawning

    int isOn = Menu(gPtr);
    
    while (isOn) {
        DisplayBoard(g.board);

        if(g.freeTiles == 0){
            printf("if no possible merge, game over (to be implemented)\n");
        }

        hasMoved = PromptMove(&isOn, gPtr);
        while(!hasMoved){
            hasMoved = PromptMove(&isOn, gPtr);
        }
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
