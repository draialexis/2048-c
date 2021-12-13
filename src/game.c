#include "../include/game.h"

Game *MakeGame() {
    Game *res = NULL;
    res = (Game *) malloc(sizeof(Game));
    if (res == NULL) { MALLOC_FAIL }
    return res;
}

void InitGame(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game to initialize\n");
        FAIL_OUT
    }
    g->board = MakeBoard();
    g->score = 0;
    g->free_tiles = 16;
    g->millisecs = 0;
    g->wasMove = 0;
    g->status = 0;
    SpawnTiles(g, 2, 2);
}

void DisplayGame(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game to display\n");
        FAIL_OUT
    }
    //refresh the screen
    SDL_FreeSurface(g->screen);
    MyFillRect(g->screen, NULL, g->screen_clr);

    SDL_Rect pos;

    pos.x = PAD, pos.y = PAD;//1st line
    char *prompt_str = "(s)auver | (c)harger";
    SDL_Surface *prompt_dis = MyRenderText(g->fnt, prompt_str, g->fnt_clr);
    MyBlit(prompt_dis, NULL, g->screen, &pos);

    pos.y += H_T; //2nd line
    char score_str[32];
    sprintf(score_str, "score : %d", g->score);
    SDL_Surface *score_dis = MyRenderText(g->fnt, score_str, g->fnt_clr);
    MyBlit(score_dis, NULL, g->screen, &pos);

    pos.y += H_T;//3rd line
    char time_str[32];
    sprintf(time_str, "secondes : %d", (int) g->millisecs / 1000);
    SDL_Surface *time_dis = MyRenderText(g->fnt, time_str, g->fnt_clr);
    MyBlit(time_dis, NULL, g->screen, &pos);

    pos.y = HDR + PAD; //1st tile
    SDL_Surface *tile = NULL;
    char val_str[5];
    Uint32 clr;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int val_int = g->board[i][j];
            switch (val_int) {//hardcode a color scheme
                case 0:
                    clr = SDL_MapRGB(g->screen->format, 230, 230, 230);
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
                    fprintf(stderr, "something went wrong\n");
                    DEBUG
                    break;
            }
            //print every tile with color according to value
            tile = SDL_CreateRGBSurface(SDL_HWSURFACE, TIL, TIL, BPP, 0, 0, 0, 0);
            MyFillRect(tile, NULL, clr);
            MyBlit(tile, NULL, g->screen, &pos);

            //print value of every tile inside each tile
            if (val_int != 0) {
                sprintf(val_str, "%d", val_int);
                SDL_Color sea = {24, 153, 211};
                SDL_Rect pos_val;
                //aiming for center of tile
                int size_x, size_y;
                TTF_SizeText(g->fnt, val_str, &size_x, &size_y);
                pos_val.x = (short) (pos.x + (TIL / 2) - (size_x / 2));
                pos_val.y = (short) (pos.y + (TIL / 2) - (size_y / 2));
                SDL_Surface *val_dis = MyRenderText(g->fnt, val_str, sea);
                MyBlit(val_dis, NULL, g->screen, &pos_val);
                SDL_FreeSurface(val_dis);
            }
            //move right in inner loop
            pos.x += TIL + PAD;
        }
        //move back left then down in outer loop
        pos.x = PAD;
        pos.y += TIL + PAD;
    }
    //display new information
    MyFlip(g->screen);
    SDL_FreeSurface(prompt_dis);
    SDL_FreeSurface(score_dis);
    SDL_FreeSurface(time_dis);
    SDL_FreeSurface(tile);
}

void FreeGame(Game *g) {
    if (g != NULL) {
        FreeBoard(g->board);
        SDL_FreeSurface(g->screen);
        TTF_CloseFont(g->fnt);
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
        fprintf(stderr, "could not find board to initialize\n");
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
        fprintf(stderr, "could not find board to copy\n");
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
        fprintf(stderr, "could not find game to use for menu\n");
        FAIL_OUT
    }
    //screen first appears here in menu before game start (new, loaded...)
    //init screen
    SDL_Surface *screen_ = NULL;
    screen_ = SDL_SetVideoMode(WID, HEI, BPP, SDL_HWSURFACE);
    if (screen_ == NULL) {
        fprintf(stderr, "\nVideoMode error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    g->screen_clr = SDL_MapRGB(screen_->format, 200, 200, 200);
    MyFillRect(screen_, NULL, g->screen_clr);
    SDL_WM_SetCaption("2048", NULL);
    g->screen = screen_;

    //init font
    TTF_Font *fnt_ = NULL;
    char *fntPath = "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf";
    fnt_ = TTF_OpenFont(fntPath, 24);
    if (fnt_ == NULL) {
        fprintf(stderr, "\nUnable to load TTF font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    g->fnt = fnt_;
    g->fnt_clr = (SDL_Color) {33, 33, 33};

    //then print menu
    SDL_Rect pos;
    pos.x = PAD, pos.y = PAD;
    SDL_Surface *menu_dis = MyRenderText(g->fnt, "(n)ouveau | (c)harger", g->fnt_clr);
    MyBlit(menu_dis, NULL, g->screen, &pos);
    MyFlip(g->screen);

    //then wait for an event
    SDL_Event evt;
    while (1) {
        MyWait(&evt);
        switch (evt.type) {
            case SDL_QUIT://can't call FreeGame() yet because some components haven't been malloced
            quit:;
                TTF_CloseFont(g->fnt);
                SDL_FreeSurface(menu_dis);
                SDL_FreeSurface(g->screen);
                TTF_Quit();
                SDL_Quit();
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto quit;
                    case 'n':
                        SDL_FreeSurface(menu_dis);
                        InitGame(g);
                        return 1;
                    case 'c':
                        if (LoadGame(g)) {//loads game if a save file exists
                            SDL_FreeSurface(menu_dis);
                            return 1;
                        } else {
                            SDL_FreeSurface(menu_dis);
                            fprintf(stderr, "could not find save or save is corrupted\n");
                            return Menu(g);
                        }
                    default:
                        SDL_FreeSurface(menu_dis);
                        return Menu(g);
                }
        }
    }
}

void SaveGame(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game to save\n");
        FAIL_OUT
    }
    char *fname = "data/save.txt";
    FILE *fp = NULL;
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
        fprintf(fp, "%d ", g->millisecs);
        fprintf(fp, "%d ", g->wasMove);
        fclose(fp);
    } else {
        FAIL_OUT
    }
}

int LoadGame(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game object to load onto\n");
        FAIL_OUT
    }
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
        fscanf(fp, "%d ", &tmp);
        g->millisecs = tmp;
        fscanf(fp, "%d ", &tmp);
        g->wasMove = tmp;
        g->isOn = 1;
        g->status = 0;
        fclose(fp);
        return 1;
    } else {
        return 0;
    }
}

void SpawnTiles(Game *g, int val, int n) {
    if (g == NULL || (val != 2 && val != 4) || (n != 1 && n != 2)) {
        fprintf(stderr, "could not find game to spawn tiles, or other invalid param\n");
        FAIL_OUT
    }
    int spawned = 0; // number of tiles spawned
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

void PromptMove(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game to prompt move\n");
        FAIL_OUT
    }
    g->wasMove = 0;
    SDL_Event evt;

    Uint32 prv_time = g->millisecs;//milliseconds ellapsed since last iteration
    if (SDL_PollEvent(&evt)) {
        switch (evt.type) {
            case SDL_QUIT:
                g->isOn = 0;
                break;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        g->isOn = 0;
                        break;
                    case SDLK_UP://rotate 90°, slide to right, rotate another 270°
                        Rotate(g->board, 1);
                        g->wasMove = Move(g);
                        Rotate(g->board, 3);
                        break;
                    case SDLK_RIGHT://slide to right
                        g->wasMove = Move(g);
                        break;
                    case SDLK_DOWN://rotate 270°, slide to right, rotate another 90°
                        Rotate(g->board, 3);
                        g->wasMove = Move(g);
                        Rotate(g->board, 1);
                        break;
                    case SDLK_LEFT://rotate 180°, slide to right, rotate another 180°
                        Rotate(g->board, 2);
                        g->wasMove = Move(g);
                        Rotate(g->board, 2);
                        break;
                    case 's':
                        SaveGame(g);
                        break;
                    case 'c':
                        LoadGame(g);
                        break;
                    case 'n':
                        InitGame(g);
                        break;
                    default:
                        break;//TODO not a good idea
                }
        }
    }
    g->millisecs = SDL_GetTicks();//milliseconds ellapsed since SDL_Init
    Uint32 passed = g->millisecs - prv_time;//time passed in this iteration
    if (passed < ITV) {
        SDL_Delay(ITV - passed);
    }
}

int Move(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game to do move\n");
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
    if (g == NULL || hasMoved == NULL) {
        fprintf(stderr, "could not find game to do slide, or other invalid param\n");
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
    if (g == NULL || hasFused == NULL) {
        fprintf(stderr, "could not find game to do fuse, or other invalid param\n");
        FAIL_OUT
    }
    //fuse to right; we use matrix rotation to take care of other directions
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (g->board[i][j] != 0 && g->board[i][j + 1] == g->board[i][j]) {
                int newVal = g->board[i][j + 1] << 1;
                if (newVal == 2048) {
                    g->status = 1;
                }
                g->score += newVal;
                g->board[i][j + 1] = newVal;
                g->board[i][j] = 0;
                *hasFused = 1;
                g->free_tiles += 1;
            }
        }
    }
}

void Rotate(int **board, int n) {
    if (board == NULL || n < 1 || n > 3) {
        fprintf(stderr, "could not find board to rotate, or other invalid param\n");
        FAIL_OUT
    }
    for (int a = 0; a < n; a++) {
        int **aux = CopyBoard(board); // original copy of board
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
        fprintf(stderr, "could not find game to check lose\n");
        FAIL_OUT
    }
    if (g->free_tiles > 0) {
        fprintf(stderr, "Uh oh -- there are free tiles on board, we shouldn't be checking for game over\n");
        DEBUG
        return;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (g->board[i][j] == g->board[i][j + 1] ||
                g->board[i][j] == g->board[i + 1][j]) {
                return;
                //a move is possible: we exit before reaching "you lose""
            }
        }
    }
    g->status = 2;//no move was possible, set status to "lose"
}

int EndGame(Game *g) {
    if (g == NULL) {
        fprintf(stderr, "could not find game to end\n");
        FAIL_OUT
    }
    SDL_Rect *hdr = NULL;// header that will contain "game over" info
    hdr = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    if (hdr == NULL) { MALLOC_FAIL }
    hdr->x = 0;
    hdr->y = 0;
    hdr->w = WID;
    hdr->h = HDR;
    //paste that header onto previous screen, but not the board
    MyFillRect(g->screen, hdr, SDL_MapRGB(g->screen->format, 180, 180, 180));

    SDL_Rect pos;

    pos.x = PAD, pos.y = PAD;//1st line
    char gameover_str[64];
    if (g->status == 2) { sprintf(gameover_str, "Game Over... (m)enu ?"); }
    else if (g->status == 1) { sprintf(gameover_str, "2 0 4 8 !.. (m)enu ?"); }
    SDL_Surface *gameover_dis = MyRenderText(g->fnt, gameover_str, g->fnt_clr);
    MyBlit(gameover_dis, NULL, g->screen, &pos);

    pos.y += H_T;//2nd line
    char score_str[64];
    sprintf(score_str, "score final : %d", g->score);
    SDL_Surface *score_dis = MyRenderText(g->fnt, score_str, g->fnt_clr);
    MyBlit(score_dis, NULL, g->screen, &pos);
    MyFlip(g->screen);

    //wait for player input
    SDL_Event evt;
    MyWait(&evt);
    switch (evt.type) {
        case SDL_QUIT:
        quit:;
            SDL_FreeSurface(score_dis);
            SDL_FreeSurface(gameover_dis);
            free(hdr);
            FreeGame(g);
            TTF_Quit();
            SDL_Quit();
            exit(EXIT_SUCCESS);
        case SDL_KEYDOWN:
            switch (evt.key.keysym.sym) {
                case 'm':
                    SDL_FreeSurface(score_dis);
                    SDL_FreeSurface(gameover_dis);
                    free(hdr);
                    return 1;
                case SDLK_ESCAPE:
                    goto quit;
                default:
                    SDL_FreeSurface(score_dis);
                    SDL_FreeSurface(gameover_dis);
                    free(hdr);
                    break;
            }
    }
    return EndGame(g);
}
