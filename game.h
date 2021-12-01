#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

int **MakeBoard();

void DisplayBoard(int **T);

void FreeBoard(int **board);

int menu(int **board, int *scorePtr);

int checkQuit(int **board, int *scorePtr, int input);

void newGame(int **board, int *scorePtr);

void loadGame();

void saveGame();

int youWin(int **board, int score);

int spawnTile(int **board, int val);

#endif //INC_2048_C_GAME_H
