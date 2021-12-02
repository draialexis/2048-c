#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

typedef struct Game_ {
    int **board;
    int score;
    int freeTiles;
    int isOn;

} Game;

Game* MakeGame();

void InitGame(Game *gPtr);

int **MakeBoard();

void InitBoard(int **T);

int PromptMove(int *isOn, Game *gPtr);

int Slide(Game *gPtr);

void DisplayBoard(int **T);

void FreeBoard(int **T);

void FreeGame(Game *gPtr);

int Menu(Game *gPtr);

int CheckStay(Game *gPtr, int input);

void NewGame(Game *gPtr);

void LoadGame();

void SaveGame();

int YouWin(Game *gPtr);

int SpawnTile(Game *gPtr, int val);

void CleanCheck();

void Rotate(int **b);

#endif //INC_2048_C_GAME_H
