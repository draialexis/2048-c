//// Walid EL CHEIK, Alexis DRAI, 17/12/2021

#include "../include_b/toolbox_b.h"
#include "../include_b/game_b.h"

Game *MakeGame() {
    Game *res = NULL;
    res = (Game *) malloc(sizeof(Game));
    if (res == NULL) { MALLOC_FAIL }
    return res;
}

void InitGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to initialize\n");
        FAIL_OUT
    }
    g->board = MakeBoard();
    g->score = 0;
    g->free_tiles = 16;
    SpawnTiles(g, 2, 2);
}

void DisplayGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to display\n");
        FAIL_OUT
    }
    printf("score: %d\n", g->score);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (g->board[i][j] != 0) { printf("%04d ", g->board[i][j]); }
            else { printf("#### "); }
        }
        printf("\n");
    }
}

void FreeGame(Game *g) {
    if (g != NULL) {
        FreeBoard(g->board);
        free(g);
    }
}

unsigned short int **MakeBoard() {
    unsigned short int **board = NULL;
    board = malloc(4 * sizeof(unsigned short int *));
    if (board == NULL) { MALLOC_FAIL }
    for (int i = 0; i < 4; i++) {
        board[i] = NULL;
        board[i] = malloc(4 * (sizeof(unsigned short int)));
        if (board[i] == NULL) {
            FreeBoard(board);
            MALLOC_FAIL
        }
    }
    InitBoard(board);
    return board;
}

void InitBoard(unsigned short int **board) {
    if (board == NULL) {
        printf("could not find board to initialize\n");
        FAIL_OUT
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
}

void FreeBoard(unsigned short int **board) {
    if (board != NULL) {
        for (int i = 0; i < 4; i++) {
            if (board[i] != NULL) { free(board[i]); }
        }
        free(board);
    }
}

unsigned short int **CopyBoard(unsigned short int **board) {
    if (board == NULL) {
        printf("could not find board to copy\n");
        FAIL_OUT
    }
    unsigned short int **res = MakeBoard();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = board[i][j];
        }
    }
    return res;
}

int Menu(Game *g) {
    if (g == NULL) {
        printf("could not find game to use for menu\n");
        FAIL_OUT
    }
    printf("=_=_=_=_=_ 2048 _=_=_=_=_=\n"
           "nouvelle partie:. n\n"
           "charger partie:.. c\n"
           "quitter:......... q\n"
           ">");

    int input = GetInput();

    switch (input) {
        case 'n':
            InitGame(g);
            return 1;
        case 'c':
            if (LoadGame(g)) {
                return 1;
            } else {
                printf("sauvegarde introuvable ou impossible a lire\n");
                return Menu(g);
            }
        case 'q':
            return 0;
        default:
            printf("requete non comprise\n");
            return Menu(g);
    }
}

void SaveGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to save\n");
        FAIL_OUT
    }
    printf("sauvegarde...\n");
    FILE *fp = NULL;
    char *fname = "console/data_b/save.txt";
    fp = fopen(fname, "w+");
    if (isFOpen(fp, fname)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                fprintf(fp, "%hu ", g->board[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "%hu ", g->score);
        fprintf(fp, "%hu ", g->free_tiles);
        fclose(fp);
        printf("partie sauvegardee\n");
    } else {
        FAIL_OUT
    }
}


int LoadGame(Game *g) {
    if (g == NULL) {
        printf("could not find game object to load onto\n");
        FAIL_OUT
    }
    printf("chargement...\n");
    FILE *fp = NULL;
    char *fname = "console/data_b/save.txt";
    fp = fopen(fname, "r");
    if (isFOpen(fp, fname)) {
        unsigned short int tmp;
        InitGame(g);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                fscanf(fp, "%hu ", &tmp);
                g->board[i][j] = tmp;
            }
            fscanf(fp, "\n");
        }
        fscanf(fp, "%hu ", &tmp);
        g->score = tmp;
        fscanf(fp, "%hu ", &tmp);
        g->free_tiles = tmp;
        printf("partie chargee\n");
        fclose(fp);
        return 1;
    } else {
        return 0;
    }
}

void SpawnTiles(Game *g, unsigned short int val, int n) {
    if (g == NULL || (val != 2 && val != 4) || (n != 1 && n != 2)) {
        printf("could not find game to spawn tiles, or other invalid param\n");
        FAIL_OUT
    }
    int spawned = 0; // number of tiles successfully spawned
    while (spawned < n) {
        int col = rand() % 4;
        int row = rand() % 4;
        if (g->board[row][col] == 0) {
            g->board[row][col] = val;
            g->free_tiles -= 1;
            spawned++;
        }
    }
}

void PromptMove(int *isOn, int *wasMove, Game *g) {
    if (g == NULL || isOn == NULL) {
        printf("could not find game tp prompt move, or other invalid param\n");
        FAIL_OUT
    }
    printf("(h)aut | (d)roite | (g)auche | (b)as || (q)uitter | (s)auvegarder | (c)harger\n");

    int input = GetInput();
    int isSuccess = 0; //boolean: was input valid and/or was move fruitful?
    *wasMove = 0;
    int input_bis;
    switch (input) {
        case 'h': //UP: rotate 90??, slide to right, rotate another 270??
            Rotate(g->board, 1);
            isSuccess = Move(g);
            Rotate(g->board, 3);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'd': //RIGHT: slide to right
            isSuccess = Move(g);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'b': //DOWN: rotate 270??, slide to right, rotate another 90??
            Rotate(g->board, 3);
            isSuccess = Move(g);
            Rotate(g->board, 1);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'g': //LEFT: rotate 180??, slide to right, rotate another 180??
            Rotate(g->board, 2);
            isSuccess = Move(g);
            Rotate(g->board, 2);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'q':
            printf("sauvegarder avant de quitter?\n"
                   "oui:... o\n"
                   "non:... n\n"
                   ">");

            input_bis = GetInput();
            if (input_bis != 'n') { SaveGame(g); }
            isSuccess = 1;
            *isOn = 0;
            break;
        case 's':
            SaveGame(g);
            isSuccess = 1;
            break;
        case 'c':
            LoadGame(g);
            isSuccess = 1;
            break;
        default:
            printf("commande non valide\n");
            break;
    }
    if (!isSuccess) {
        printf("mouvement impossible\n");
    }
}

int Move(Game *g) {
    if (g == NULL) {
        printf("could not find game to do move\n");
        FAIL_OUT
    }
    int hasMoved = 0; //boolean: has any move happened?
    int hasFused = 0; //boolean: has any fusion happened?
    //slide tiles
    Slide(g, &hasMoved);
    //fuse tiles
    Fuse(g, &hasFused);
    //slide tiles again if at least one fusion
    if (hasFused) { Slide(g, &hasMoved); }
    //if something happened, let main() know  turn is accomplished
    if (hasMoved || hasFused) { return 1; }
        //if nothing happened, let main() know so player can try a different move
    else { return 0; }
}

void Slide(Game *g, int *hasMoved) {
    if (g == NULL) {
        printf("could not find game to do slide, or other invalid param\n");
        FAIL_OUT
    }
    //slide to right; we use matrix rotation to take care of other directions
    for (int a = 0; a < 3; a++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) {
                if (g->board[i][j + 1] == 0 && g->board[i][j] != 0) {
                    g->board[i][j + 1] = g->board[i][j];
                    g->board[i][j] = 0;
                    *hasMoved = 1;
                }
            }
        }
    }
}

void Fuse(Game *g, int *hasFused) {
    if (g == NULL) {
        printf("could not find game to do fuse, or other invalid param\n");
        FAIL_OUT
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (g->board[i][j] != 0 && g->board[i][j + 1] == g->board[i][j]) {
                int newVal = g->board[i][j + 1] << 1;
                g->score += newVal;
                if (newVal == 2048) { YouWin(g); }
                g->board[i][j + 1] = newVal;
                g->board[i][j] = 0;
                g->free_tiles += 1;
                *hasFused = 1;
            }
        }
    }
}

void Rotate(unsigned short int **board, int n) {
    if (board == NULL || n < 1 || n > 3) {
        printf("could not find board to rotate, or other invalid param\n");
        FAIL_OUT
    }
    for (int a = 0; a < n; a++) {
        unsigned short int **aux = CopyBoard(board); // original copy of board
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                board[j][3 - i] = aux[i][j];
            }
        }
        FreeBoard(aux);
    }
}

void CheckLose(Game *g) {
    if (g == NULL) {
        printf("could not find game to check lose\n");
        FAIL_OUT
    }
    if (g->free_tiles > 0) {
        printf("Uh oh -- there are free tiles on board, we shouldn't be checking for game over\n");
        DEBUG
        return;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (g->board[i][j] == g->board[i][j + 1] ||
                g->board[i][j] == g->board[i + 1][j]) {
                return;
                //a move is possible: we exit before reaching YouLose(), player can figure it out
            }
        }
    }
    YouLose(g);
}

void YouLose(Game *g) {
    if (g == NULL) {
        printf("could not find game to lose\n");
        FAIL_OUT
    }
    printf("=====Game Over=====\nvotre score final: %d\n", g->score);
    FreeGame(g);
    exit(EXIT_SUCCESS);
}

void YouWin(Game *g) {
    if (g == NULL) {
        printf("could not find game to win\n");
        FAIL_OUT
    }
    printf("Felicitations! \\_2_0_4_8_/\nvotre score final: %d\n", g->score);
    FreeGame(g);
    exit(EXIT_SUCCESS);
}


