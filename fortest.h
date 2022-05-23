
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "struct.h"

using namespace std;
#ifndef FORTEST_H
#define FORTEST_H
/*void testChessPieceMove()
{
    ChessPiece duy;
    duy.type=2;
    duy.myLocation=pair<int,int>(7,3);
    duy.UpdateSquareCanMove(game.board);
    duy.GetSquareCanMove();
    drawChessBoard(game.renderer);
    drawChessPiece(duy,game.renderer);
    SDL_RenderPresent(game.renderer);
    SDL_Delay(100);
}
*/
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
