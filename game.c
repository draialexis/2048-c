#include "game.h"
#include "toolbox.h"


Game* MakeGame(){
    Game * res = NULL;
    res = (Game*) malloc(sizeof(Game));
    if(res==NULL){
        MALLOC_FAIL
    }
    return res;
}

//function that initiates the 4x4 table.(it has no parameters since the size is already set)
int **MakeBoard(){
    int **T = NULL;
    T =  malloc(4*sizeof(int*));
    if(T==NULL){
        MALLOC_FAIL
    }
    for(int i=0;i<4;i++){
        T[i] = NULL;
        T[i] = malloc(4*(sizeof(int)));
        if(T[i]==NULL){
            FreeBoard(T);
            MALLOC_FAIL
        }
    }
    InitBoard(T);
    return T;
}

void InitGame(Game *gPtr) {
    gPtr->board = MakeBoard();
    gPtr->score = 0;
    gPtr->freeTiles = 16;
}

void InitBoard(int **T){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            T[i][j] = 0;
        }
    }
}

//board display
void DisplayBoard(int **T){
    int x;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(T==NULL){
                //TODO error msg?
                exit(0);
            }
            x = T[i][j];
            if(x != 0) {printf("%d ", x);} else {printf("# ");}
        }
        printf("\n");
    }
    printf("\n");
}

void FreeBoard(int **T){
    if(T != NULL){
        for(int i = 0; i < 4; i++) {
            if(T[i] != NULL){
                free(T[i]);
            }
        }
        free(T);
    }
}

void FreeGame(Game *gPtr){
    if(gPtr != NULL){
        FreeBoard(gPtr->board);
    }
    free(gPtr);
}

int PromptMove(int *isOn, Game *gPtr) {
    printf("make a move\n");
    int input = getc(stdin);
    CleanCheck();
    *isOn = CheckStay(gPtr, input);
    int success = 0;
    //TODO deal with all other valid inputs (dgbh)
    switch(input){
        case 'd':
            success = Slide(gPtr);
            break;
        case 'h':
            Rotate(gPtr->board);
            success = Slide(gPtr);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            break;
        case 'g':
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            success = Slide(gPtr);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            break;
        case 'b':
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            Rotate(gPtr->board);
            success = Slide(gPtr);
            Rotate(gPtr->board);
            break;
        default:
            PromptMove(isOn, gPtr);
    }
    return success;
}

void CleanCheck() {
    getchar();
    fflush(stdin);
}

int Slide(Game *gPtr){
    // slide to the right, we'll use matrix rotation to take care of the other directions
    int moves = 0, fusions = 0;
    int newVal, i, j, k, a;

    for(a = 0; a < 3; a++){ //TODO optimize instead of applying worst case every time
        for(i = 0; i < 4; i++){
            for (j = 2; j >=0; j--){
                if(gPtr->board[i][j + 1] == 0 && gPtr->board[i][j] != 0){
                    gPtr->board[i][j + 1] = gPtr->board[i][j];
                    gPtr->board[i][j] = 0;
                    moves++;
                }
            }
        }
    }

    for(i = 0; i < 4; i++){
        for(j= 2; j >= 0; j--){
            if(gPtr->board[i][j] != 0 && gPtr->board[i][j + 1] == gPtr->board[i][j]){
                newVal = gPtr->board[i][j + 1] << 1;
                gPtr->score += newVal;
                gPtr->board[i][j + 1] = newVal;
                gPtr->board[i][j] = 0;
                gPtr->freeTiles += 1;
                fusions++;

                for(k = j+1; k < 3; k++){ //move n° 2, only useful when there's a double merge in one row
                    if(gPtr->board[i][k + 1] == 0 && gPtr->board[i][k] != 0){
                        gPtr->board[i][k + 1] = gPtr->board[i][k];
                        gPtr->board[i][k] = 0;
                        moves++;
                    }
                }
            }
        }
    }

    //fusion goes here

    if(moves || fusions) {
        return 1;
    } else {
        return 0;
    }
}

void Rotate(int **b) {
    int ** aux = MakeBoard();
    //CopyBoard(b, aux);
    int rows = 4;
    int cols = 4;
    for (int i = 0; i < rows; i++) {
        for (int j = cols - 1; j >= 0; j--) {
                b[i][cols - 1 - j] = aux[j][i];           // yadda yadda... use AUX matrix or tmp var
        }
    }
    DisplayBoard(b);
}



int Menu(Game *gPtr) {
    printf("=_=_=_=_=_=_=_= 2048 =_=_=_=_=_=_=_=\n"
           "nouvelle partie:. n\n"
           "charger partie:.. l\n"
           "quitter:......... q\n"
           ">");

    int input = getc(stdin);
    CleanCheck();

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
    int spawned = 0;
    while (spawned < 2) {
        spawned += SpawnTile(gPtr, 2);
    }
}

void SaveGame() {
    printf("saveGame(): to be implemented...\n");
    //TODO implement
    //csv-style file? easy format, 1st value is b[0][0], 2nd is b[0][1]... 16th is b[3][3], 17th (last) is the score
}

void LoadGame() {
    printf("loadGame(): to be implemented...\n");
    //TODO implement
    //use the save file to fill the board and the score

}

int CheckStay(Game *gPtr, int input) {
    //if the player types inputs 'q' during the game (instead of a move), we offer a save before exiting to menu
    if (input == 'q') {
        printf("sauvegarder avant de quitter?\n"
               "oui:... o\n"
               "non:... n\n"
               ">");

        int input_bis = getc(stdin);
        CleanCheck();

        if (input_bis == 'n') {
            return Menu(gPtr);
        } else {
            SaveGame();
            return Menu(gPtr);
        }
    }
    return 1; //
}

int YouWin(Game *gPtr) {
    printf("felicitations! vous avez atteint \\_2_0_4_8_/\n"
           "votre score final: %d\n", gPtr->score);
    return Menu(gPtr);
}

int SpawnTile(Game *gPtr, int val) {
    //TODO ? instead use a list of (x, y) coordinates (updated during play, containing all free tiles)
    int row = rand() % 4;
    int col = rand() % 4;

    if (gPtr->board[row][col] == 0) {
        gPtr->board[row][col] = val;
        gPtr->freeTiles -= 1;
        return 1;
    } else {
        return 0;
    }
}


