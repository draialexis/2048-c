#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

int **MakeBoard();

int PromptMove(int *isOn, int **board, int *scorePtr);

int SlideBoard(int **board, int * score);

void DisplayBoard(int **T);

void FreeBoard(int **board);

int Menu(int **board, int *scorePtr);

int CheckStay(int **board, int *scorePtr, int input);

void NewGame(int **board, int *scorePtr);

void LoadGame();

void SaveGame();

int YouWin(int **board, int score);

int SpawnTile(int **board, int val);

void CleanCheck();

void Rotate(int **b);

void InitBoard(int **T);

#endif //INC_2048_C_GAME_H
