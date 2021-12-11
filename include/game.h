#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

#define HEI 640 //height of screen
#define WID 480 //width of screen
#define H_B 480 //width of screen
#define W_B 480 //width of screen
#define HDR (HEI - WID) //height of header for score and timer
#define PAD 10 //size of padding
#define TIL ((WID - (PAD * 5)) / 4) //length of a tile's side
#define BPP 32 //bits per pixel

/**
 * a struct to represent a game of 2048
 * @property board: a pointer to a 4x4 matrix of ints
 * @property score: an int for player's score
 * @property free_tiles: an int for remaining number of free tiles (val=0) on board
 */
typedef struct Game_ {
    int **board;
    int score;
    int free_tiles;
} Game;

/**
 * allocates memory for a Game
 * @return a pointer to an uninitialized Game
 */
Game *MakeGame();

/**
 * initializes a Game: allocating memory for board, setting all values to 0, score to 0
 * and free_tiles to 16
 * @param g a pointer to a Game
 */
void InitGame(Game *g);

/**
 * displays a Game to console, showing state of board and score
 * @param g a pointer to a Game
 * @param screen a pointer to a SDL_Surface
 * @param fnt a pointer to a TTF_Font
 */
void DisplayGame(Game *g, SDL_Surface *screen, TTF_Font *fnt);

/**
 * frees memory allocated to a Game
 * @param g a pointer to a Game
 */
void FreeGame(Game *g);

/**
 * allocates memory for a 4x4 matrix of ints, i.e. a 2048 board, then setting all values to 0
 * @return a pointer to board
 */
int **MakeBoard();

/**
 * initializes a 4x4 matrix of ints, i.e. a 2048 board, setting all values to 0
 * @param board a pointer to a board
 */
void InitBoard(int **board);

/**
 * displays a 4x4 matrix of ints, i.e. a 2048 board, to console, with 4 leading 0s and with '#'s on empty tiles
 * @param board a pointer to a board
 * @param screen a pointer to a SDL_Surface
 * @param fnt a pointer to a TTF_Font
 */
void DisplayBoard(int **board, SDL_Surface *screen, TTF_Font *fnt);

/**
 * frees memory allocated to a 4x4 matrix of ints, i.e. a 2048 board
 * @param board a pointer to a board
 */
void FreeBoard(int **board);

/**
 * makes a copy of a 4x4 matrix of ints, i.e. a 2048 board
 * @param board a pointer to a board
 * @return a pointer to a copy of given board
 */
int **CopyBoard(int **board);

/**
 * prompts user for an input, with options to start a new Game, load a Game, or exit program
 * @param g a pointer to a Game
 * @param screen a pointer to a SDL_Surface
 * @param fnt a pointer to a TTF_Font
 * @return if exit: 0; else: 1
 */
int Menu(Game *g, SDL_Surface *screen, TTF_Font *fnt);

/**
 * starts a new Game, setting all to default initial values, and spawning two 2s at random spots on board
 * @param g a pointer to a Game
 * @param g a pointer to a SDL_Surface
 */
void NewGame(Game *g, SDL_Surface *screen);

/**
 * saves a Game to a unique .txt save file in program's root folder, with a default name: 'save_2048.txt'
 * @param g a pointer to a Game
 */
void SaveGame(Game *g);

/**
 * loads a Game from a unique .txt save file in program's root folder, with a default name: 'save_2048.txt'
 * @param g a pointer to a Game
 * @return if a file was able to be loaded, 1; else, 0
 */
int LoadGame(Game *g);

/**
 * sets a number of random '0-locations' in a 4x4 matrix of ints, i.e. a 2048 board, to certain values;
 * decrements a Game's free_tiles property after each addition
 * @param g a pointer to a Game
 * @param val a value to be placed on board; must be 2 or 4
 * @param n number of '0-locations' to be set; must be 1 or 2
 */
void SpawnTiles(Game *g, int val, int n);

/**
 * executes user input for a move, with options for 'up', 'right', 'down', and 'left'; as well as for saving, quitting,
 * and both
 * @param isOn a pointer to a boolean, that can tell main() if Game must go on; set to 0 if quitting
 * @param wasMove a pointer to a pseudo-boolean, that can tell main() if last action was a move; else, no spawn
 * @param g a pointer to a Game
 * @param fnt a pointer to a TTF_Font
 */
void PromptMove(int *isOn, int *wasMove, Game *g, SDL_Surface *screen, TTF_Font *fnt);

/**
 * accomplishes a move in a Game by sliding and fusing tiles to right
 * @param g a pointer to a Game
 * @return if move invalid: 1; else: 0 (nothing happened)
 */
int Move(Game *g);

/**
 * slides all tiles from a 4x4 matrix of ints, i.e. a 2048 board, to right, until they encounter an obstacle, where
 * they stop
 * @param g a pointer to a Game
 * @param hasMoved a pointer to a boolean, that can tell Move() if any tiles moved; set to 0 if not
 */
void Slide(Game *g, int *hasMoved);

/**
 * fuses all tiles with identical values, who neighbor each other horizontally, from right to left; right-hand tile
 * receives new doubled value while other receives 0; a freshly doubled tile will not play part in another fusion;
 * if any fusion was winning, i.e. produced 2048, go to win screen and exit
 * @param g a pointer to a Game
 * @param hasFused a pointer to a boolean, that can tell Move() if any tiles fused; set to 0 if not
 */
void Fuse(Game *g, int *hasFused);

/**
 * rotates a 4x4 matrix of ints, i.e. a 2048 board, 90 deg to right
 * @param board a pointer to a board
 * @param n number of rotations wanted; must be 1, 2, or 3
 */
void Rotate(int **board, int n);

/**
 * looks for two neighbouring identical values in a 4x4 matrix of ints, i.e. a 2048 board, with no 0s; if a pair is
 * found, return void, else: go to game over
 * @param g a pointer to a Game
 */
void CheckLose(Game *g);

/**
 * prints a game over screen, frees memory allocated to Game, and exits program
 * @param g a pointer to a Game
 */
void YouLose(Game *g);

/**
 * prints a win screen, frees memory allocated to Game, and exits program
 * @param g a pointer to a Game
 */
void YouWin(Game *g);

#endif //INC_2048_C_GAME_H
