#include "game.h"
#include "toolbox.h"

int menu(int **board, int *scorePtr) {
    printf("=_=_=_=_=_=_=_= 2048 =_=_=_=_=_=_=_=\n"
           "nouvelle partie:. n\n"
           "charger partie:.. l\n"
           "quitter:......... q\n"
           ">");

    int input = getc(stdin);
    fflush(stdin);

    switch (input) {
        case 'n':
            newGame(board, scorePtr);
            return 1;
        case 'l':
            loadGame();
            return 1;
        case 'q': //if the player inputs 'q' in the menu, we exit the program
            return 0;
        default:
            printf("requete non comprise\n");
            return menu(board, scorePtr);
    }
}

void newGame(int **board, int *scorePtr) {
    *scorePtr = 0;
    board = MakeBoard();

    int spawned = 0;
    while (spawned < 2) {
        spawned += spawnTile(board, 2);
    }
}

void saveGame() {
    DEBUG
    printf("saveGame(): to be implemented...\n");
    //TODO implement
    //csv-style file? easy format, 1st value is b[0][0], 2nd is b[0][1]... 16th is b[3][3], 17th (last) is the score
}

void loadGame() {
    DEBUG
    printf("loadGame(): to be implemented...\n");
    //TODO implement
    //use the save file to fill the board and the score

}

int checkQuit(int input) {
    //if the player types inputs 'q' during the game (instead of a move), we offer a save before exiting to menu
    if (input == 'q') {
        printf("sauvegarder avant de quitter?\n"
               "oui:... o\n"
               "non:... n\n"
               ">");

        int input_bis = getc(stdin);
        fflush(stdin);

        if (input_bis == 'n') {
            return menu();
        } else {
            saveGame();
            return menu();
        }
    }
}

int youWin(int score) {
    printf("felicitations! vous avez atteint \\_2_0_4_8_/\n"
           "votre score final: %d\n", score);
    return menu();
}

int spawnTile(int **board, int val) {
    //TODO ? instead use a list of (x, y) coordinates (updated during play, containing all free tiles)
    int x = rand() % 4;
    int y = rand() % 4;
    if (board[x][y] == 0) {
        board[x][y] = val;
        return 1;
    } else {
        spawnTile(board, val);
    }
}


