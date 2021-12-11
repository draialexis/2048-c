#include <SDL.h>// TODO remove later?
#include <SDL_ttf.h>// TODO remove later?
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

void DisplayGame(Game *g, SDL_Surface *screen, TTF_Font *fnt) {
    if (g == NULL) {
        printf("could not find game to display\n");
        FAIL_OUT
    }

//    printf("score: %d\n", g->score);
    //TODO TTF stuff
    /*
    SDL_Rect pos;
    pos.x = 500;
    pos.y = 30;
    SDL_Surface *menu = NULL;
    SDL_Color charcoal = {33, 33, 33};
    menu = TTF_RenderText_Blended(fnt, "(n)ew | (l)oad | (q)uit", charcoal);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 150, 150, 150));
    SDL_BlitSurface(menu, NULL, screen, &pos);
    SDL_Flip(screen);

     */

    DisplayBoard(g->board, screen, fnt);
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

void DisplayBoard(int **board, SDL_Surface *screen, TTF_Font *fnt) {
    if (board == NULL) {
        printf("could not find board to display\n");
        FAIL_OUT
    }
    SDL_Rect pos;
    pos.x = 0;
    pos.y = HDR;
    SDL_Surface *tile = NULL, *sdl_board = NULL;

    sdl_board = SDL_CreateRGBSurface(SDL_HWSURFACE, W_B, H_B, BPP, 0, 0, 0, 0);
    SDL_FillRect(sdl_board, NULL, SDL_MapRGB(screen->format, 200, 200, 200));
    SDL_BlitSurface(sdl_board, NULL, screen, &pos);

    pos.x += PAD;
    pos.y += PAD;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Uint32 clr;
            int val_int = board[i][j];
            switch (val_int) {
                case 0:
                    clr = SDL_MapRGB(screen->format, 250, 250, 250);
                    break;
                case 2:
                    clr = SDL_MapRGB(screen->format, 235, 215, 188);
                    break;
                case 4:
                    clr = SDL_MapRGB(screen->format, 222, 189, 146);
                    break;
                case 8:
                    clr = SDL_MapRGB(screen->format, 215, 175, 123);
                    break;
                case 16:
                    clr = SDL_MapRGB(screen->format, 202, 153, 87);
                    break;
                case 32:
                    clr = SDL_MapRGB(screen->format, 185, 131, 57);
                    break;
                case 64:
                    clr = SDL_MapRGB(screen->format, 151, 106, 47);
                    break;
                case 128:
                    clr = SDL_MapRGB(screen->format, 132, 64, 45);
                    break;
                case 256:
                    clr = SDL_MapRGB(screen->format, 109, 53, 37);
                    break;
                case 512:
                    clr = SDL_MapRGB(screen->format, 89, 44, 30);
                    break;
                case 1024:
                    clr = SDL_MapRGB(screen->format, 70, 34, 23);
                    break;
                case 2048:
                    clr = SDL_MapRGB(screen->format, 48, 36, 33);
                    break;
                default:
                    clr = SDL_MapRGB(screen->format, 255, 0, 0);
                    //this should never happen
                    break;
            }
            tile = SDL_CreateRGBSurface(SDL_HWSURFACE, TIL, TIL, BPP, 0, 0, 0, 0);
            SDL_FillRect(tile, NULL, clr);
            SDL_BlitSurface(tile, NULL, screen, &pos);
            if (val_int != 0) {
                char val_str[5];
                sprintf(val_str, "%d", val_int);
                SDL_Color sea = {24, 153, 211};
                SDL_Surface *tile_val = TTF_RenderText_Blended(fnt, val_str, sea);
                SDL_Rect pos_val;
                pos_val.x = (short) (pos.x + PAD);
                pos_val.y = (short) (pos.y + PAD);
                SDL_BlitSurface(tile_val, NULL, screen, &pos_val);
            }
            pos.x += TIL + PAD;
        }
        pos.x = PAD;
        pos.y += TIL + PAD;
    }
    SDL_Flip(screen);
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

int Menu(Game *g, SDL_Surface *screen, TTF_Font *fnt) {
    if (g == NULL || screen == NULL) {
        printf("could not find game to use for menu, or other missing parameter\n");
        FAIL_OUT
    }

    SDL_Rect pos;
    pos.x = PAD;
    pos.y = PAD;
    SDL_Surface *menu = NULL;
    SDL_Color charcoal = {33, 33, 33};
    menu = TTF_RenderText_Blended(fnt, "(n)ouveau | (c)harger", charcoal);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 200, 200, 200));
    SDL_BlitSurface(menu, NULL, screen, &pos);
    SDL_Flip(screen);

    int isOn = 1;
    SDL_Event evt;
    while (isOn) {
        SDL_WaitEvent(&evt);
        switch (evt.type) {
            case SDL_QUIT:
                SDL_FreeSurface(menu);
                return 0;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case 'n':
                        SDL_FreeSurface(menu);
                        NewGame(g, screen);
                        return 1;
                    case 'c':
                        if (LoadGame(g)) {
                            SDL_FreeSurface(menu);
                            return 1;
                        } else {
                            printf("sauvegarde introuvable ou impossible a lire\n");
                            return Menu(g, screen, fnt);
                        }
                        break;
                    default:
                        printf("commande non comprise\n");
                        return Menu(g, screen, fnt);
                }
        }
    }
    return 0; // cannot be reached, in practice...
}

void NewGame(Game *g, SDL_Surface *screen) {
    if (g == NULL || screen == NULL) {
        printf("could not find game or screen to start\n");
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

void PromptMove(int *isOn, int *wasMove, Game *g, SDL_Surface *screen, TTF_Font *fnt) {
    if (g == NULL || isOn == NULL) {
        printf("could not find game tp prompt move, or other invalid param\n");
        FAIL_OUT
    }

    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    SDL_Surface *header = NULL;
    header = SDL_CreateRGBSurface(SDL_HWSURFACE, W_B, HDR, BPP, 0, 0, 0, 0);
    SDL_FillRect(header, NULL, SDL_MapRGB(screen->format, 200, 200, 200));
    SDL_BlitSurface(header, NULL, screen, &pos);

    pos.x = PAD;
    pos.y = PAD;
    SDL_Surface *prompt = NULL;
    SDL_Color charcoal = {33, 33, 33};
    prompt = TTF_RenderText_Blended(fnt, "(s)auver | (c)harger", charcoal);
    SDL_BlitSurface(prompt, NULL, screen, &pos);
    SDL_Flip(screen);

    int isSuccess = 0; //boolean: was input valid and/or was move fruitful?
    *wasMove = 0;
    SDL_Event evt;
    SDL_WaitEvent(&evt);
    switch (evt.type) {
        case SDL_QUIT:
            *isOn = 0;
            break;
        case SDL_KEYDOWN:
            switch (evt.key.keysym.sym) {
                case SDLK_UP://UP: rotate 90°, slide to right, rotate another 270°
                    Rotate(g->board, 1);
                    isSuccess = Move(g);
                    Rotate(g->board, 3);
                    if (isSuccess) { *wasMove = 1; }
                    break;
                case SDLK_RIGHT://RIGHT: slide to right
                    isSuccess = Move(g);
                    if (isSuccess) { *wasMove = 1; }
                    break;
                case SDLK_DOWN://DOWN: rotate 270°, slide to right, rotate another 90°
                    Rotate(g->board, 3);
                    isSuccess = Move(g);
                    Rotate(g->board, 1);
                    if (isSuccess) { *wasMove = 1; }
                    break;
                case SDLK_LEFT://LEFT: rotate 180°, slide to right, rotate another 180°
                    Rotate(g->board, 2);
                    isSuccess = Move(g);
                    Rotate(g->board, 2);
                    if (isSuccess) { *wasMove = 1; }
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
                    break;
            }
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
