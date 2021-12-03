#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

typedef struct Game_ {
    int **board;
    int score;
    int freeTiles;
    int isOn;

} Game;

Game *MakeGame();

void InitGame(Game *gPtr);

void DisplayGame(Game *gPtr);

void FreeGame(Game *gPtr);

int **MakeBoard();

void InitBoard(int **T);

void DisplayBoard(int **T);

void FreeBoard(int **T);

int Menu(Game *gPtr);

void NewGame(Game *gPtr);

void LoadGame();

void SaveGame();

void SpawnTiles(Game *gPtr, int val, int num);

int PromptMove(int *isOn, Game *gPtr);

int Slide(Game *gPtr);

void Rotate(int **b);

int CheckStay(Game *gPtr, int input);

void CheckLose(Game *gPtr);

void YouLose(Game *gPtr);

void YouWin(Game *gPtr);

#endif //INC_2048_C_GAME_H
