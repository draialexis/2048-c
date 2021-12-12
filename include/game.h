#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

#define HEI 640 //height of screen
#define WID 480 //width of screen
#define HDR (HEI - WID) //height of header for score and timer
#define PAD 10 //size of padding
#define H_T 30 //(approx) height of text
#define TIL ((WID - (PAD * 5)) / 4) //length of a tile's side
#define BPP 32 //bits per pixel

#include "toolbox.h"

/**
 * a struct to represent a game of 2048
 * @properties board: a pointer to a 4x4 matrix of ints, i.e. a 2048 board
 * @properties score: an int for player score
 * @properties seconds: an int number of seconds passed since start of game
 * @properties isOn: boolean: is game on?
 * @properties wasMove: boolean: was the last action actually a move?
 * @properties status: 1 for win, 2 for lose, 0 for nothing
 * @properties screen: a pointer to an SDL_Surface
 * @properties fnt: a pointer to a TTF_Font
 * @properties fnt_clr: a pointer to an SDL_Color
 */
typedef struct Game_ {
    int **board;
    int score;
    int seconds;
    int isOn;
    int wasMove;
    int status;
    SDL_Surface *screen;
    TTF_Font *fnt;
    SDL_Color fnt_clr;
} Game;

/**
 * allocates memory for a Game
 * @return a pointer to an uninitialized Game
 */
Game *MakeGame();

/**
 * initializes a Game: allocating memory for board, setting all values to 0, score to 0
 * @param g a pointer to a Game
 */
void InitGame(Game *g);

/**
 * displays a Game to console, showing state of board and score
 * @param g a pointer to a Game
 */
void DisplayGame(Game *g);

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
 * @return if exit: 0; else: 1
 */
int Menu(Game *g);

/**
 * starts a new Game, setting all to default initial values, and spawning two 2s at random spots on board
 * @param g a pointer to a Game
 */
void NewGame(Game *g);

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
 * @param g a pointer to a Game
 * @param val a value to be placed on board; must be 2 or 4
 * @param n number of '0-locations' to be set; must be 1 or 2
 */
void SpawnTiles(Game *g, int val, int n);

/**
 * executes user input for a move, with options for 'up', 'right', 'down', and 'left'; as well as for saving, quitting,
 * both, and loading
 * @param g a pointer to a Game
 */
void PromptMove(Game *g);

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
int CheckStatus(Game *g);

/**
 * prints a game over screen and shows final score (win or lose)
 * @param g a pointer to a Game
 * @return if wants to go back to menu, 1; else, 0, frees memory allocated to Game, and exits program
 */
int EndGame(Game *g);

#endif //INC_2048_C_GAME_H
