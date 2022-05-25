
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "struct.h"

using namespace std;            //include function to test logic game by iostream
#ifndef FORTEST_H
#define FORTEST_H

void printChessBoardNum(vector<vector<int>> &board)
{
    for (unsigned int i=0;i<board.size();i++){
        for (unsigned int j=0;j<board[0].size();j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

#endif // FORTEST_H
