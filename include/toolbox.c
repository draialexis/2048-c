#include "toolbox.h"

void Purge() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void load(int **board) {
    int i, j;
    FILE *fp = fopen("save.txt", "r");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            fscanf(fp, "%d ", &board[i][j]);
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
}

void save(int **board) {
    int i, j;
    FILE *fp = fopen("save.txt", "w");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            fprintf(fp, "%d ", board[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}