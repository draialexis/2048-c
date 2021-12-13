#ifndef INC_2048_C_GAME_H
#define INC_2048_C_GAME_H

#define HEI 640 //height of screen
#define WID 480 //width of screen
#define HDR (HEI - WID) //height of header for score and timer
#define PAD 10 //size of padding
#define H_T 30 //(approx) height of text
#define TIL ((WID - (PAD * 5)) / 4) //length of a tile's side
#define BPP 32 //bits per pixel
#define ITV 38 //interval wanted between two frames, in ms (around 26FPS)

#include "toolbox.h"

/**
 * a struct to represent a game of 2048
 * @properties board: pointer to a 4x4 matrix of ints, i.e. a 2048 board
 * @properties score: int, player score
 * @properties free_tiles: int, number of remaining 0-tiles on board
 * @properties millisecs: Uint32, time since start of game in milliseconds
 * @properties isOn: "boolean", is game on?
 * @properties wasMove: "boolean", was last action actually a move?
 * @properties status: 1 for win, 2 for lose, 0 for normal
 * @properties screen: pointer to an SDL_Surface
 * @properties screen_clr: Uint32 color, typically built from SDL_MapRGB()
 * @properties fnt: pointer to a TTF_Font
 * @properties fnt_clr: pointer to an SDL_Color
 */
typedef struct Game_ {
    int **board;
    int score;
    int free_tiles;
    Uint32 millisecs;
    int isOn;
    int wasMove;
    int status;
    SDL_Surface *screen;
    Uint32 screen_clr;
    TTF_Font *fnt;
    SDL_Color fnt_clr;
} Game;

/**
 * allocates memory for a Game
 * @return a pointer to an uninitialized Game
 */
Game *MakeGame();

/**
 * initializes a Game: allocating memory for board, setting all values to initial state
 * and spawning two 2s at random spots on board
 * @param g a pointer to a Game
 */
void InitGame(Game *g);

/**
 * displays a Game to screen, showing state of board, a reduced menu, a score and a timer
 * @param g a pointer to a Game
 */
void DisplayGame(Game *g);

/**
 * frees memory allocated to a Game, including surface and font
 * @param g a pointer to a Game
 */
void FreeGame(Game *g);

/**
 * allocates memory for a 4x4 matrix of ints, i.e. a 2048 board, then setting all values to 0
 * @return a pointer to board
 */
int **MakeBoard();

/**
 * initializes a 4x4 matrix of ints, i.e. a 2048 board, by setting all values to 0
 * @param board a pointer to a board
 */
void InitBoard(int **board);

/**
 * frees memory allocated to a 4x4 matrix of ints, i.e. a 2048 board
 * @param board a pointer to a board
 */
void FreeBoard(int **board);

/**
 * makes a copy of a given 4x4 matrix of ints, i.e. a 2048 board
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
 * saves a Game to a unique .txt save file in program's root folder, with a default name: 'save.txt'
 * @param g a pointer to a Game
 */
void SaveGame(Game *g);

/**
 * loads a Game from a unique .txt save file in program's root folder, with a default name: 'save.txt'
 * @param g a pointer to a Game
 * @return if a file was able to be loaded, 1; else, 0
 */
int LoadGame(Game *g);

/**
 * sets a given number of random '0-locations' in a Game board to a given value
 * @param g a pointer to a Game
 * @param val a value to be placed on board; must be 2 or 4
 * @param n number of '0-locations' to be set; must be 1 or 2
 */
void SpawnTiles(Game *g, int val, int n);

/**
 * executes user input for a move, with options for 'up', 'right', 'down', and 'left'; as well as for saving, quitting,
 * and loading
 * @param g a pointer to a Game
 */
void PromptMove(Game *g);

/**
 * accomplishes a move on a Game board by trying to slide and fuse tiles to right
 * @param g a pointer to a Game
 * @return if move was valid: 1; else: 0 (nothing happened)
 */
int Move(Game *g);

/**
 * slides all tiles from a Game board to right, until they encounter an obstacle, where they stop
 * @param g a pointer to a Game
 * @param hasMoved if slide was valid: 1; else: 0 (nothing happened)
 */
void Slide(Game *g, int *hasMoved);

/**
 * fuses all tiles from a Game board with identical values, who neighbor each other horizontally, from right to left;
 * right-hand tile receives new doubled value while other receives 0; a freshly doubled tile will not play part in
 * another fusion
 * @param g a pointer to a Game
 * @param hasFused a pointer to a boolean, that can tell Move() if any tiles fused; set to 0 if not
 */
void Fuse(Game *g, int *hasFused);

/**
 * rotates a 4x4 matrix of ints, i.e. a 2048 board, 90 degrees to right
 * @param board a pointer to a board
 * @param n number of rotations wanted; must be 1, 2, or 3
 */
void Rotate(int **board, int n);

/**
 * looks for two neighbouring identical values in a Game board with no 0s; if a pair is
 * found, return void, else: set Game status to 2 for lose
 * @param g a pointer to a Game
 */
void CheckLose(Game *g);

/**
 * prints a 'you win' / 'you lose' screen, shows final score, offers path to menu
 * @param g a pointer to a Game
 * @return if go back to menu, 1; else, 0, frees memory allocated to Game, and exits program
 */
int EndGame(Game *g);

#endif //INC_2048_C_GAME_H
