#include "toolbox.h"
#include "game.h"


int main() {

    int isOn = menu();

    while (isOn) {

        //the player input
        int input = getc(stdin);
        fflush(stdin);
        isOn = checkQuit(input);
        //TODO deal with all other valid inputs
    }

    return 0;
}