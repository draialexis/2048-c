#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

int menu(int **board, int *scorePtr);

int checkQuit(int input);

void newGame(int **board, int *scorePtr);

void loadGame();

void saveGame();

int youWin(int score);

int spawnTile(int **board, int val);

#endif //INC_2048_C_GAME_H
