#include "game.h"

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
    g->seconds = 0;
    g->wasMove = 0;
    g->status = 0;
}

void DisplayGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to display\n");
        FAIL_OUT
    }
    SDL_Rect pos;

    char *prompt_str = "(s)auver | (c)harger";

    pos.x = PAD;
    pos.y = PAD;//1st line
    SDL_Surface *prompt = NULL;
    prompt = TTF_RenderText_Blended(g->fnt, prompt_str, g->fnt_clr);
    SDL_BlitSurface(prompt, NULL, g->screen, &pos);

    pos.x = PAD;
    pos.y = PAD + H_T; //2nd line
    SDL_Surface *score_dis = NULL;
    char score_str[32];
    sprintf(score_str, "score : %d", g->score);
    score_dis = TTF_RenderText_Blended(g->fnt, score_str, g->fnt_clr);
    SDL_BlitSurface(score_dis, NULL, g->screen, &pos);

    pos.x = 0;
    pos.y = HDR;
    SDL_Surface *tile = NULL;

    pos.x += PAD;
    pos.y += PAD;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Uint32 clr;
            int val_int = g->board[i][j];
            switch (val_int) {
                case 0:
                    clr = SDL_MapRGB(g->screen->format, 250, 250, 250);
                    break;
                case 2:
                    clr = SDL_MapRGB(g->screen->format, 235, 215, 188);
                    break;
                case 4:
                    clr = SDL_MapRGB(g->screen->format, 222, 189, 146);
                    break;
                case 8:
                    clr = SDL_MapRGB(g->screen->format, 215, 175, 123);
                    break;
                case 16:
                    clr = SDL_MapRGB(g->screen->format, 202, 153, 87);
                    break;
                case 32:
                    clr = SDL_MapRGB(g->screen->format, 185, 131, 57);
                    break;
                case 64:
                    clr = SDL_MapRGB(g->screen->format, 151, 106, 47);
                    break;
                case 128:
                    clr = SDL_MapRGB(g->screen->format, 132, 64, 45);
                    break;
                case 256:
                    clr = SDL_MapRGB(g->screen->format, 109, 53, 37);
                    break;
                case 512:
                    clr = SDL_MapRGB(g->screen->format, 89, 44, 30);
                    break;
                case 1024:
                    clr = SDL_MapRGB(g->screen->format, 70, 34, 23);
                    break;
                case 2048:
                    clr = SDL_MapRGB(g->screen->format, 48, 36, 33);
                    break;
                default:
                    clr = SDL_MapRGB(g->screen->format, 255, 0, 0);
                    //this should never happen
                    break;
            }
            tile = SDL_CreateRGBSurface(SDL_HWSURFACE, TIL, TIL, BPP, 0, 0, 0, 0);
            SDL_FillRect(tile, NULL, clr);
            SDL_BlitSurface(tile, NULL, g->screen, &pos);
            if (val_int != 0) {
                char val_str[5];
                sprintf(val_str, "%d", val_int);
                SDL_Color sea = {24, 153, 211};
                SDL_Surface *tile_val = TTF_RenderText_Blended(g->fnt, val_str, sea);
                SDL_Rect pos_val;
                pos_val.x = (short) (pos.x + PAD);
                pos_val.y = (short) (pos.y + PAD);
                SDL_BlitSurface(tile_val, NULL, g->screen, &pos_val);
            }
            pos.x += TIL + PAD;
        }
        pos.x = PAD;
        pos.y += TIL + PAD;
    }
    SDL_Flip(g->screen);
    SDL_FreeSurface(prompt);
    SDL_FreeSurface(score_dis);
    SDL_FreeSurface(tile);
}

void FreeGame(Game *g) {
    if (g != NULL) {
        FreeBoard(g->board);
        SDL_FreeSurface(g->screen);
        TTF_CloseFont(g->fnt);
        free(g);
        TTF_Quit();
        SDL_Quit();
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

int Menu(Game *g) {
    if (g == NULL) {
        printf("could not find game to use for menu\n");
        FAIL_OUT
    }

    //the screen first appears in the menu before we start a game (new, loaded...)
    //so we initialize the screen and font here
    SDL_Surface *screen_ = NULL;
    screen_ = SDL_SetVideoMode(WID, HEI, BPP, SDL_HWSURFACE);
    if (screen_ == NULL) {
        fprintf(stderr, "\nVideoMode error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FillRect(screen_, NULL, SDL_MapRGB(screen_->format, 230, 230, 230));
    SDL_WM_SetCaption("2048", NULL);
    g->screen = screen_;

    char *fntPath = "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf";
    TTF_Font *fnt_ = NULL;
    fnt_ = TTF_OpenFont(fntPath, 24);
    if (fnt_ == NULL) {
        fprintf(stderr, "\nUnable to load TTF font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    g->fnt = fnt_;
    g->fnt_clr = (SDL_Color) {33, 33, 33};

    SDL_Rect pos;
    pos.x = PAD;
    pos.y = PAD;
    SDL_Surface *menu = NULL;
    menu = TTF_RenderText_Blended(g->fnt, "(n)ouveau | (c)harger", g->fnt_clr);
    SDL_BlitSurface(menu, NULL, g->screen, &pos);

    SDL_Flip(g->screen);

    SDL_Event evt;
    while (1) {
        SDL_WaitEvent(&evt);
        switch (evt.type) {
            case SDL_QUIT:// we can't call freegame because some components haven't been malloced yet
                TTF_CloseFont(g->fnt);
                SDL_FreeSurface(menu);
                SDL_FreeSurface(g->screen);
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        TTF_CloseFont(g->fnt);
                        SDL_FreeSurface(menu);
                        SDL_FreeSurface(g->screen);
                        exit(EXIT_SUCCESS);
                    case 'n':
                        SDL_FreeSurface(menu);
                        NewGame(g);
                        return 1;
                    case 'c':
                        if (LoadGame(g)) {//loads game if a save file exists
                            SDL_FreeSurface(menu);
                            return 1;
                        } else {
                            SDL_FreeSurface(menu);
                            printf("sauvegarde introuvable ou impossible a lire\n");
                            return Menu(g);
                        }
                        break;
                    default:
                        SDL_FreeSurface(menu);
                        return Menu(g);
                }
        }
    }
    return 0; // cannot be reached, in practice...
}

void NewGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to start\n");
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
        fprintf(fp, "%d ", g->seconds);
        fprintf(fp, "%d ", g->wasMove);
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
        g->seconds = tmp;
        fscanf(fp, "%d ", &tmp);
        g->wasMove = tmp;
        g->isOn = 1;
        g->status = 0;
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
            spawned++;
        }
    }
}

void PromptMove(Game *g) {
    if (g == NULL) {
        printf("could not find game to prompt move, or other invalid param\n");
        FAIL_OUT
    }

    int isSuccess = 0; //boolean: was input valid and/or was move fruitful?
    g->wasMove = 0;
    SDL_Event evt;
    SDL_WaitEvent(&evt);
    switch (evt.type) {
        case SDL_QUIT:
            g->isOn = 0;
            break;
        case SDL_KEYDOWN:
            switch (evt.key.keysym.sym) {
                case SDLK_ESCAPE:
                    g->isOn = 0;
                    break;
                case SDLK_UP://UP: rotate 90°, slide to right, rotate another 270°
                    Rotate(g->board, 1);
                    isSuccess = Move(g);
                    Rotate(g->board, 3);
                    if (isSuccess) { g->wasMove = 1; }
                    break;
                case SDLK_RIGHT://RIGHT: slide to right
                    isSuccess = Move(g);
                    if (isSuccess) { g->wasMove = 1; }
                    break;
                case SDLK_DOWN://DOWN: rotate 270°, slide to right, rotate another 90°
                    Rotate(g->board, 3);
                    isSuccess = Move(g);
                    Rotate(g->board, 1);
                    if (isSuccess) { g->wasMove = 1; }
                    break;
                case SDLK_LEFT://LEFT: rotate 180°, slide to right, rotate another 180°
                    Rotate(g->board, 2);
                    isSuccess = Move(g);
                    Rotate(g->board, 2);
                    if (isSuccess) { g->wasMove = 1; }
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
                g->score += newVal;
                g->board[i][j + 1] = newVal;
                g->board[i][j] = 0;
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

int CheckStatus(Game *g) {
    if (g == NULL) {
        printf("could not find game to check status\n");
        FAIL_OUT
    }
    int isFree = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (g->board[i][j] == 2048) { return 1; }
            if (g->board[i][j] == 0) { isFree = 1; }
            if (i < 3 && j < 3) {
                if (g->board[i][j] == g->board[i][j + 1] ||
                    g->board[i][j] == g->board[i + 1][j]) {
                    isFree = 1;
                }
            }
        }
    }
    if (isFree) {
        return 0;
    } else {
        return 2;
    }
}

int EndGame(Game *g) {
    if (g == NULL) {
        printf("could not find game to end\n");
        FAIL_OUT
    }
    SDL_Rect *hdr = NULL;
    hdr = (SDL_Rect *) malloc(sizeof(SDL_Rect)); // a header that will contain game over info
    if (hdr == NULL) {
        DEBUG
        MALLOC_FAIL
    }
    hdr->x = 0;
    hdr->y = 0;
    hdr->w = WID;
    hdr->h = HDR;
    SDL_FillRect(g->screen, hdr, SDL_MapRGBA(g->screen->format, 150, 150, 150, 200));

    SDL_Rect pos;

    pos.x = PAD;
    pos.y = PAD;
    char score_str[64] = "";
    sprintf(score_str, "score final : %d", g->score);
    SDL_Surface *score_dis = TTF_RenderText_Blended(g->fnt, score_str, g->fnt_clr);
    SDL_BlitSurface(score_dis, NULL, g->screen, &pos);

    pos.y += H_T;
    char gameover[64];
    if (g->status == 2) {
        sprintf(gameover, "Game Over... (m)enu ?");
    } else if (g->status == 1) {
        sprintf(gameover, "2 0 4 8 !.. (m)enu ?");
    }
    SDL_Surface *gameover_dis = TTF_RenderText_Blended(g->fnt, gameover, g->fnt_clr);
    SDL_BlitSurface(gameover_dis, NULL, g->screen, &pos);

    SDL_Flip(g->screen);
    SDL_Event evt;
    SDL_WaitEvent(&evt);
    switch (evt.type) {
        case SDL_QUIT:
            SDL_FreeSurface(score_dis);
            SDL_FreeSurface(gameover_dis);
            free(hdr);
            FreeGame(g);
            exit(EXIT_SUCCESS);
        case SDL_KEYDOWN:
            switch (evt.key.keysym.sym) {
                case 'm':
                    SDL_FreeSurface(score_dis);
                    SDL_FreeSurface(gameover_dis);
                    free(hdr);
                    return 1;
                case SDLK_ESCAPE:
                    SDL_FreeSurface(score_dis);
                    SDL_FreeSurface(gameover_dis);
                    free(hdr);
                    FreeGame(g);
                    exit(EXIT_SUCCESS);
                default:
                    SDL_FreeSurface(score_dis);
                    SDL_FreeSurface(gameover_dis);
                    free(hdr);
                    break;
            }
    }
    return EndGame(g);
}
