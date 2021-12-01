#include "toolbox.h"
#include "game.h"


int main() {
    srand(time(NULL));
    int **board = MakeBoard();     // the game board
    int isFull = 0;         // a boolean: is the board full?
    int hasWon = 0;         // a boolean: has the player won?
    int score;              // the current score
    int scoreUp;            // the amount by which the score will be increased
    int spawned;            // the amount of tile succesfully spawned
    int val;                // the value to record in a tile
    int freeTiles = 16;     // the number of free tiles
    int moveDone;           // a boolean: does the player need to try another move instead?
    //TODO do the pointer thingy with spawning

    int isOn = menu(board, &score);
    
    while (isOn) {
        DisplayBoard(board);
        
        moveDone = PromptMove(&isOn, board, &score);
        while(!moveDone){
            moveDone = PromptMove(&isOn, board, &score);
        }
        //board-moving goes here
        // on every merge instance
        //... counting score...
        // scoreUp = b[_][_]<<1;
        // b[_][_] = scoreUp;
        // score += scoreUp;
        // if(scoreUp == 2048) hasWon = 1;
        //... after counting all the merge score_ups ...

        if (hasWon) {
            hasWon = 0; //we've taken the win into account, we can reinit this to 0 for next game
            isOn = youWin(board, score);
        }

        if (!isFull) {
            spawned = 0;
            if (rand() % 2 == 1) { val = 2; } else { val = 4; }
            while (!spawned) {
                spawned += spawnTile(board, val);
            }
        }
    }

    return 0;
}
