#include "game.h"
#include "toolbox.h"

//TODO add validation everywhere

Game *MakeGame() {
    Game *res = NULL;
    res = (Game *) malloc(sizeof(Game));
    if (res == NULL) {
        MALLOC_FAIL
    }
    return res;
}

void InitGame(Game *gPtr) {
    gPtr->board = MakeBoard();
    gPtr->score = 0;
    gPtr->freeTiles = 16;
}

void DisplayGame(Game *gPtr) {
    printf("score: %d\n", gPtr->score);
//    printf("free tiles: %d\n", gPtr->freeTiles);
    DisplayBoard(gPtr->board);
}

void FreeGame(Game *gPtr) {
    if (gPtr != NULL) {
        FreeBoard(gPtr->board);
    }
    free(gPtr);
}

int **MakeBoard() {
    int **T = NULL;
    T = malloc(4 * sizeof(int *));
    if (T == NULL) {
        MALLOC_FAIL
    }
    for (int i = 0; i < 4; i++) {
        T[i] = NULL;
        T[i] = malloc(4 * (sizeof(int)));
        if (T[i] == NULL) {
            FreeBoard(T);
            MALLOC_FAIL
        }
    }
    InitBoard(T);
    return T;
}

void InitBoard(int **T) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            T[i][j] = 0;
        }
    }
}

void DisplayBoard(int **T) {
    int x;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (T == NULL) {
                //TODO error msg?
                exit(0);
            }
            x = T[i][j];
            if (x != 0) { printf("%04d ", x); } else { printf("#### "); }
        }
        printf("\n");
    }
    printf("\n");
}

void FreeBoard(int **T) {
    if (T != NULL) {
        for (int i = 0; i < 4; i++) {
            if (T[i] != NULL) {
                free(T[i]);
            }
        }
        free(T);
    }
}

int **CopyBoard(int **b) {
    int **res = MakeBoard();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[i][j] = b[i][j];
        }
    }
    return res;
}

int Menu(Game *gPtr) {
    printf("=_=_=_=_=_=_=_= 2048 =_=_=_=_=_=_=_=\n"
           "nouvelle partie:. n\n"
           "charger partie:.. l\n"
           "quitter:......... q\n"
           ">");

    int input = getchar();
    Purge();

    switch (input) {
        case 'n':
            NewGame(gPtr);
            return 1;
        case 'l':
            LoadGame();
            return 1;
        case 'q': //if the player inputs 'q' in the menu, we exit the program
            return 0;
        default:
            printf("requete non comprise\n");
            return Menu(gPtr);
    }
}

void NewGame(Game *gPtr) {
    InitGame(gPtr);
    SpawnTiles(gPtr, 2, 2);
}

void SaveGame() {
    printf("saveGame(): to be implemented...\n");
    //TODO implement
    //csv-style file? easy format, 1st is b[0][0], 2nd is b[0][1]... 16th is b[3][3], 17th is the score, 18th is free tiles
}

void LoadGame() {
    printf("loadGame(): to be implemented...\n");
    //TODO implement
    //use the save file to fill the board and the score

}

void SpawnTiles(Game *gPtr, int val, int num) {
    //TODO ? instead use a list of (x, y) coordinates (updated during play, containing all free tiles)
    int spawned = 0;
    while (spawned < num) {
        int col = rand() % 4;
        int row = rand() % 4;
        if (gPtr->board[row][col] == 0) {
//            printf("[%d][%d] = %d\n", row, col, val);
            gPtr->board[row][col] = val;
            gPtr->freeTiles -= 1;
            spawned++;
        }
    }
}

void PromptMove(int *isOn, Game *gPtr) {
//    printf("(h)aut | (d)roite | (g)auche | (b)as || (q)uitter\n");
//TODO reimplement gdbh before submitting

    int input = getchar();
    Purge();
    int success = 0;
    switch (input) {
        case 'd':
            success = Slide(gPtr);
            break;
        case 'z': //rotate 90°, slide to the right, rotate another 270°
            Rotate(gPtr->board);
            success = Slide(gPtr);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            break;
        case 'q': //rotate 180°, slide to the right, rotate another 180°
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            success = Slide(gPtr);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            break;
        case 's': //rotate 270°, slide to the right, rotate another 90°
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            success = Slide(gPtr);
            Rotate(gPtr->board);
            break;
        case 'Q':
            printf("sauvegarder avant de quitter?\n"
                   "oui:... o\n"
                   "non:... n\n"
                   ">");

            int input_bis = getchar();
            Purge();

            if (input_bis != 'n') { SaveGame(); }
            success = 1;
            *isOn = 0;
            break;
        default:
            printf("commande non valide\n");
            break;
    }
    if (!success) {
        printf("mouvement impossible\n");
        PromptMove(isOn, gPtr);
    }
}

int Slide(Game *gPtr) {
    // slide to the right, we'll use matrix rotation to take care of the other directions

    //TODO decide if we keep the counters moves and fusions
    int moves = 0, fusions = 0; //counters, to see if the move was valid
    int hasWon = 0; //pseudo-boolean
    int newVal, i, j, a;

    //moving tiles
    for (a = 0; a < 3; a++) { //TODO optimize instead of applying worst case every time
        for (i = 0; i < 4; i++) {
            for (j = 2; j >= 0; j--) {
                if (gPtr->board[i][j + 1] == 0 && gPtr->board[i][j] != 0) {
                    gPtr->board[i][j + 1] = gPtr->board[i][j];
                    gPtr->board[i][j] = 0;
                    moves++;
                }
            }
        }
    }

    //fusing tiles
    for (i = 0; i < 4; i++) {
        for (j = 2; j >= 0; j--) {
            if (gPtr->board[i][j] != 0 && gPtr->board[i][j + 1] == gPtr->board[i][j]) {
                newVal = gPtr->board[i][j + 1] << 1;
                if (newVal == 2048) {
                    hasWon = 1;
                }
                gPtr->score += newVal;
                gPtr->board[i][j + 1] = newVal;
                gPtr->board[i][j] = 0;
                gPtr->freeTiles += 1;
                fusions++;
            }
        }
    }

    //moving tiles again if there has been at least one fusion from the player input
    if (fusions) {
        for (a = 0; a < 3; a++) { //TODO optimize also
            for (i = 0; i < 4; i++) {
                for (j = 2; j >= 0; j--) {
                    if (gPtr->board[i][j + 1] == 0 && gPtr->board[i][j] != 0) {
                        gPtr->board[i][j + 1] = gPtr->board[i][j];
                        gPtr->board[i][j] = 0;
                        moves++;
                    }
                }
            }
        }
    }

    if (moves || fusions) {
        if (hasWon) {
            YouWin(gPtr);
        }
        return 1;
    } else {
        return 0;
    }
}

void Rotate(int **b) {
    int **aux = CopyBoard(b);
    int rows = 4;
    int cols = 4;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            b[j][3 - i] = aux[i][j];
        }
    }
    FreeBoard(aux);
}

void CheckLose(Game *gPtr) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (gPtr->board[i][j] == gPtr->board[i][j + 1]
                || gPtr->board[i][j] == gPtr->board[i + 1][j]) {
                return; //a move is possible: we exit before reaching YouLose, the player can figure it out
            }
        }
    }
    YouLose(gPtr);
}

void YouLose(Game *gPtr) {
    printf("=====Game Over=====\n"
           "votre score final: %d\n", gPtr->score);
    FreeGame(gPtr);
    //TODO delete savefile if exists?
    exit(EXIT_SUCCESS);
}

void YouWin(Game *gPtr) {
    printf("Felicitations! vous avez atteint \\_2_0_4_8_/\n"
           "votre score final: %d\n", gPtr->score);
    FreeGame(gPtr);
    exit(EXIT_SUCCESS);
}


