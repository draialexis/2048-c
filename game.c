#include "game.h"
#include "toolbox.h"

//TODO add validation everywhere

Game *MakeGame() {
    Game *res = NULL;
    res = (Game *) malloc(sizeof(Game));
    if (res == NULL) { MALLOC_FAIL }
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
        free(gPtr);
    }
}

int **MakeBoard() {
    int **T = NULL;
    T = malloc(4 * sizeof(int *));
    if (T == NULL) { MALLOC_FAIL }
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
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (T[i][j] != 0) { printf("%04d ", T[i][j]); }
            else { printf("#### "); }
        }
        printf("\n");
    }
}

void FreeBoard(int **T) {
    if (T != NULL) {
        for (int i = 0; i < 4; i++) {
            if (T[i] != NULL) { free(T[i]); }
        }
        free(T);
    }
}

int **CopyBoard(int **b) {
    int **res = MakeBoard();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = b[i][j];
        }
    }
    return res;
}

int Menu(Game *gPtr) {
    printf("=_=_=_=_=_ 2048 _=_=_=_=_=\n"
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
        case 'q':
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
//TODO reimplement gdbh and q before submitting

    int input = getchar();
    Purge();
    int success = 0;
    switch (input) {
        case 'd': //RIGHT
            success = DoMove(gPtr);
            break;
        case 'z': //UP:     rotate 90°, slide to the right, rotate another 270°
            Rotate(gPtr->board, 1);
            success = DoMove(gPtr);
            Rotate(gPtr->board, 3);
            break;
        case 'q': //DOWN:   rotate 180°, slide to the right, rotate another 180°
            Rotate(gPtr->board, 2);
            success = DoMove(gPtr);
            Rotate(gPtr->board, 2);
            break;
        case 's': //LEFT:   rotate 270°, slide to the right, rotate another 90°
            Rotate(gPtr->board, 3);
            success = DoMove(gPtr);
            Rotate(gPtr->board, 1);
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

int DoMove(Game *gPtr) {
    int hasMoved = 0, hasFused = 0, hasWon = 0;

    //slide tiles
    Slide(gPtr, &hasMoved);
    //fuse tiles
    Fuse(gPtr, &hasFused, &hasWon);
    //slide tiles again if at least one fusion
    if (hasFused) { Slide(gPtr, &hasMoved); }

    if (hasMoved || hasFused) { //if something happened, let main() know the turn is accomplished
        if (hasWon) { YouWin(gPtr); }
        return 1;
    } else { return 0; } //if nothing happened, let main() know so player can try a different move
}

void Slide(Game *gPtr, int *hasMoved) {
    //slide to the right; we use matrix rotation to take care of the other directions
    for (int a = 0; a < 3; a++) { //TODO ? optimize instead of applying worst case every time
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) {
                if (gPtr->board[i][j + 1] == 0 && gPtr->board[i][j] != 0) {
                    gPtr->board[i][j + 1] = gPtr->board[i][j];
                    gPtr->board[i][j] = 0;
                    *hasMoved = 1;
                }
            }
        }
    }
}

void Fuse(Game *gPtr, int *hasFused, int *hasWon) {
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (gPtr->board[i][j] != 0 && gPtr->board[i][j + 1] == gPtr->board[i][j]) {
                int newVal = gPtr->board[i][j + 1] << 1;
                if (newVal == 2048) { *hasWon = 1; }
                gPtr->score += newVal;
                gPtr->board[i][j + 1] = newVal;
                gPtr->board[i][j] = 0;
                gPtr->freeTiles += 1;
                *hasFused = 1;
            }
        }
    }
}

void Rotate(int **b, int n) {
    for (int a = 0; a < n; a++) {
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
}

void CheckLose(Game *gPtr) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gPtr->board[i][j] == gPtr->board[i][j + 1] ||
                gPtr->board[i][j] == gPtr->board[i + 1][j]) {
                return;
                //a move is possible: we exit before reaching YouLose, the player can figure it out
            }
        }
    }
    YouLose(gPtr);
}

void YouLose(Game *gPtr) {
    printf("=====Game Over=====\nvotre score final: %d\n", gPtr->score);
    FreeGame(gPtr);
    //TODO delete savefile if exists?
    exit(EXIT_SUCCESS);
}

void YouWin(Game *gPtr) {
    printf("Felicitations! \\_2_0_4_8_/\nvotre score final: %d\n", gPtr->score);
    FreeGame(gPtr);
    exit(EXIT_SUCCESS);
}


