#include <SDL.h>// TODO remove later?
#include <SDL_ttf.h>// TODO remove later?
//#include "SDL.h"//<<<<TODO remove #include before shipping
//#include "SDL_ttf.h"//<<<<TODO remove #include before shipping
#include "game.h"
#include "toolbox.h"

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
}

void DisplayGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to display\n");
        FAIL_OUT
    }
    printf("score: %d\n", g->score);
//    printf("free tiles: %d\n", g->free_tiles);
    DisplayBoard(g->board);
}

void FreeGame(Game *g) {
    if (g != NULL) {
        FreeBoard(g->board);
        free(g);
    }
}

int **MakeBoard() {
    int **board = NULL;
    board = malloc(4 * sizeof(int *));
    if (board == NULL) { MALLOC_FAIL }

    for (int i = 0; i < 4; i++) {
        board[i] = NULL;
        board[i] = malloc(4 * (sizeof(int)));
        if (board[i] == NULL) {
            FreeBoard(board);
            MALLOC_FAIL
        }
    }

    InitBoard(board);
    return board;
}

void InitBoard(int **board) {
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

void DisplayBoard(int **board) {
    if (board == NULL) {
        printf("could not find board to display\n");
        FAIL_OUT
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) { printf("%04d ", board[i][j]); }
            else { printf("#### "); }
        }
        printf("\n");
    }
}

void FreeBoard(int **board) {
    if (board != NULL) {
        for (int i = 0; i < 4; i++) {
            if (board[i] != NULL) { free(board[i]); }
        }
        free(board);
    }
}

int **CopyBoard(int **board) {
    if (board == NULL) {
        printf("could not find board to copy\n");
        FAIL_OUT
    }
    int **res = MakeBoard();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = board[i][j];
        }
    }
    return res;
}

int Menu(Game *g, SDL_Surface *screen) {
    if (g == NULL || screen == NULL) {
        printf("could not find game to use for menu, or other missing parameter\n");
        FAIL_OUT
    }
    char *fntPath = "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf";
    TTF_Font *fnt = NULL;
    fnt = TTF_OpenFont(fntPath, 24);

    SDL_Rect pos;
    pos.x = 50;
    pos.y = 50;
    SDL_Surface *menu = NULL;
    SDL_Color charcoal = {33, 33, 33};
    menu = TTF_RenderText_Blended(fnt, "(n)ew | (l)oad | (q)uit", charcoal);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 150, 150, 150));
    SDL_BlitSurface(menu, NULL, screen, &pos);
    SDL_Flip(screen);

    int isOn = 1;
    SDL_Event evt;
    while (isOn) {
        SDL_WaitEvent(&evt);
        switch (evt.type) {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDL_QUIT:
                        return 0;
                    case 'n':
                        NewGame(g);
                        return 1;
                    case 'l':
                        if (LoadGame(g)) {
                            return 1;
                        } else {
                            printf("sauvegarde introuvable ou impossible a lire\n");
                            return Menu(g, screen);
                        }
                        break;
                    case 'q':
                        return 0;
                    default:
                        printf("commande non comprise\n");
                        return Menu(g, screen);
                }
        }
    }
}

void NewGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to start new\n");
        FAIL_OUT
    }
    InitGame(g);
    SpawnTiles(g, 2, 2);
}

void SaveGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to save\n");
        FAIL_OUT
    }
    printf("sauvegarde...\n");
    FILE *fp = NULL;
    char *fname = "data/save.txt";
    fp = fopen(fname, "w+");
    if (isFOpen(fp, fname)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                fprintf(fp, "%d ", g->board[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "%d ", g->score);
        fprintf(fp, "%d ", g->free_tiles);
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
    char *fname = "data/save.txt";
    fp = fopen(fname, "r");
    if (isFOpen(fp, fname)) {
        int tmp;
        InitGame(g);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                fscanf(fp, "%d ", &tmp);
                g->board[i][j] = tmp;
            }
            fscanf(fp, "\n");
        }
        fscanf(fp, "%d ", &tmp);
        g->score = tmp;
        fscanf(fp, "%d ", &tmp);
        g->free_tiles = tmp;
        printf("partie chargee\n");
        fclose(fp);
        return 1;
    } else {
        return 0;
    }
}

void SpawnTiles(Game *g, int val, int n) {
    if (g == NULL || (val != 2 && val != 4) || (n != 1 && n != 2)) {
        printf("could not find game to spawn tiles, or other invalid param\n");
        FAIL_OUT
    }
    int spawned = 0; // number of tiles spawned
    while (spawned < n) {
        int col = rand() % 4;
        int row = rand() % 4;
        if (g->board[row][col] == 0) {
//            printf("[%d][%d] = %d\n", row, col, val);
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

    int input = getchar();
    Purge();
    int isSuccess = 0; //boolean: was input valid and/or was move fruitful?
    *wasMove = 0;
    int input_bis;
    switch (input) {
        case 'h': //UP:     rotate 90°, slide to right, rotate another 270°
            Rotate(g->board, 1);
            isSuccess = Move(g);
            Rotate(g->board, 3);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'd': //RIGHT:  slide to right
            isSuccess = Move(g);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'b': //DOWN:   rotate 270°, slide to right, rotate another 90°
            Rotate(g->board, 3);
            isSuccess = Move(g);
            Rotate(g->board, 1);
            if (isSuccess) { *wasMove = 1; }
            break;
        case 'g': //LEFT:   rotate 180°, slide to right, rotate another 180°
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

            input_bis = getchar();
            Purge();

            if (input_bis != 'n') { SaveGame(g); }
            isSuccess = 1;
            *isOn = 0;
            break;
        case 's':
            printf("ecraser la derniere sauvegarde?\n"
                   "oui:... o\n"
                   "non:... n\n"
                   ">");
            input_bis = getchar();
            Purge();
            if (input_bis == 'o') {
                SaveGame(g);
                isSuccess = 1;
            }
            break;
        case 'c':
            printf("quitter et charger la derniere sauvegarde?\n"
                   "oui:... o\n"
                   "non:... n\n"
                   ">");

            input_bis = getchar();
            Purge();
            if (input_bis == 'o') {
                LoadGame(g);
                isSuccess = 1;
            }
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
                if (newVal == 2048) { YouWin(g); }
                g->score += newVal;
                g->board[i][j + 1] = newVal;
                g->board[i][j] = 0;
                g->free_tiles += 1;
                *hasFused = 1;
            }
        }
    }
}

void Rotate(int **board, int n) {
    if (board == NULL || n < 1 || n > 3) {
        printf("could not find board to rotate, or other invalid param\n");
        FAIL_OUT
    }
    for (int a = 0; a < n; a++) {
        int **aux = CopyBoard(board); // original copy of board
        int rows = 4;
        int cols = 4;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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


