
#include <iostream>
#include <windows.h>
#include "struct.h"
#include "game.h"

using namespace std;
#undef main

int main()
{   //init game
    Game game;
    //the game loop
    while (true){
        //menu
        game.Menu();
        SDL_RenderPresent(game.renderer);
        Sleep(16);
    }
    return 0;
}

