#include <iostream>
#include "struct.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "fortest.h"

using namespace std;
#ifndef CHESSAI_H               //this header include just random move and A simple AI move
#define CHESSAI_H


vector<ChessMove> CreateValidMoveVector(const vector<vector<vector<int>>> &History,const vector<vector<int>> &board,const bool &turn,KingAndRockMoveHistory& CheckCastle);
int getRandomNumber(const int& low,const int& high) //random number from low to high [low,high]
{
    srand(time(NULL));
    return low+rand()%(high-low+1);
}
ChessMove chooseRandomAIChessMove(const vector<vector<vector<int>>> &History,const vector<vector<int>> &board,const bool &turn,KingAndRockMoveHistory& CheckCastle)
{
    vector<ChessMove> validMove=CreateValidMoveVector(History,board,turn,CheckCastle);


    return validMove[getRandomNumber(0,validMove.size()-1)];
}

vector<ChessMove> CreateValidMoveVector(const vector<vector<vector<int>>> &History,const vector<vector<int>> &board,const bool &turn,KingAndRockMoveHistory& CheckCastle)
{
    vector<ChessMove> validMove;
    //now in case turn =0, for basic option
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board[i][j]<0){
                ChessPiece x=ChessPiece(i,j,board[i][j]);
                x.UpdateSquareCanMove(board,1);
                for (unsigned int n=0;n<x.SquareCanMove.size();n++){
                    ChessMove k=ChessMove(History,CheckCastle,pair<int,int>(i,j),x.SquareCanMove[n],board,board[i][j],0,1);
                    if (k.valid()) validMove.push_back(k);
                }
            }
        }
    }
    return validMove;
}
//for my max value stable move AI
int evaluateBoard(const vector<vector<int>>& board,const bool &flip)
{
    int value=0;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board[i][j]!=0){
                ChessPiece x(i,j,board[i][j]);
                x.UpdateSquareCanMove(board,flip);
                x.updateValue();
                cout << 2*(x.SquareCanMove.size()) << " " << x.value << endl;
                value+=board[i][j]>0? (2*(x.SquareCanMove.size())):(-2*(x.SquareCanMove.size()));
                value+=x.value;
            }
        }
    }
    cout << "value is: " <<  value << endl;
    return value;
}

//stable move means always exist 1 move from our side in case the opponent move a move that make big change
// and there's no more move can make the value of the board change more than 10 value from your opponent
bool stableMove(vector<vector<int>> board,const bool &flip,int first_value,int second_value,int depth)
{
    //basic case: when there no more move can make big change from your teammate

    depth--;
    cout << "let check if stable move: \n";
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board[i][j]>0){
                ChessPiece x(i,j,board[i][j]);
                x.UpdateSquareCanMove(board,flip);
                for (unsigned int k=0;k<x.SquareCanMove.size();k++){
                    vector<vector<int>> board_=board;
                    vector<vector<vector<int>>> history;
                    KingAndRockMoveHistory KRHistory;
                    ChessMove tempMove(history,KRHistory,pair<int,int>(i,j),x.SquareCanMove[k],board_,board[i][j],0,flip);

                    //change the temp board:

                    //update board
                    board_[tempMove.secondLoc.first][tempMove.secondLoc.second]=board_[tempMove.firstLoc.first][tempMove.firstLoc.second];
                    board_[tempMove.firstLoc.first][tempMove.firstLoc.second]=0;

                    //Pawn Evolution
                    if ((board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==6 and tempMove.secondLoc.first==0 and tempMove.flip==1) or (board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==6 and tempMove.secondLoc.first==7 and tempMove.flip ==-1))
                        board_[tempMove.secondLoc.first][tempMove.secondLoc.second]=2;

                    if ((board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==-6 and tempMove.secondLoc.first==7 and tempMove.flip==1) or (board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==-6 and tempMove.secondLoc.first==0 and tempMove.flip==-1))
                        board_[tempMove.secondLoc.first][tempMove.secondLoc.second]=-2;

                    //evaluate this temp board:
                    int value_=evaluateBoard(board_,flip);
                    if (abs(first_value-value_)>=30 and depth>0) return stableMove(board_,flip,first_value,value_,depth);

                }
            }
        }
    }
    return true;
}

ChessMove AIMove(const vector<vector<int>>& board,const bool &flip)
{
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board[i][j]<0){
                ChessPiece x(i,j,board[i][j]); //x is the temp piece we consider
                x.UpdateSquareCanMove(board,flip);
                for (unsigned int k=0;k<x.SquareCanMove.size();k++){
                    vector<vector<int>> board_=board;
                    vector<vector<vector<int>>> history;
                    KingAndRockMoveHistory KRHistory;
                    ChessMove tempMove(history,KRHistory,pair<int,int>(i,j),x.SquareCanMove[k],board_,board[i][j],0,flip);
                    cout << "success init temp Move\n";
                    //change the temp board:

                    //update board_
                    board_[tempMove.secondLoc.first][tempMove.secondLoc.second]=board_[tempMove.firstLoc.first][tempMove.firstLoc.second];
                    board_[tempMove.firstLoc.first][tempMove.firstLoc.second]=0;

                    //Pawn Evolution
                    if ((board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==6 and tempMove.secondLoc.first==0 and tempMove.flip==1) or (board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==6 and tempMove.secondLoc.first==7 and tempMove.flip ==-1))
                        board_[tempMove.secondLoc.first][tempMove.secondLoc.second]=2;

                    if ((board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==-6 and tempMove.secondLoc.first==7 and tempMove.flip==1) or (board_[tempMove.secondLoc.first][tempMove.secondLoc.second]==-6 and tempMove.secondLoc.first==0 and tempMove.flip==-1))
                        board_[tempMove.secondLoc.first][tempMove.secondLoc.second]=-2;

                    printChessBoardNum(board_);
                    int first_value=evaluateBoard(board_,flip);
                    cout << "value: " << first_value << endl;
                    int second_value=0,depth=3;
                    if (stableMove(board_,flip,first_value,second_value=0,depth)) return tempMove;
                }
            }
        }
    }
    vector<vector<vector<int>>> history;
    KingAndRockMoveHistory checkCastle;
    return chooseRandomAIChessMove(history,board,0,checkCastle);
}

ChessMove simpleAIMove(const vector<vector<int>> board,const bool& flip)
{
    ChessMove highestMove;
    int minPoint=1000;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (board[i][j]<0){
                ChessPiece temp(i,j,board[i][j]);
                temp.UpdateSquareCanMove(board,flip);

                for (unsigned int k=0;k<temp.SquareCanMove.size();k++){
                    vector<vector<int>> tempBoard=board;
                    vector<vector<vector<int>>> history;
                    KingAndRockMoveHistory CheckCastle;
                    ChessMove tempMove(history,CheckCastle,pair<int,int>(i,j),temp.SquareCanMove[k],board,board[i][j],0,flip);
                    if (tempMove.valid()){
                        //Move with tempBoard
                        //update tempBoard
                        tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]=tempBoard[tempMove.firstLoc.first][tempMove.firstLoc.second];
                        tempBoard[tempMove.firstLoc.first][tempMove.firstLoc.second]=0;

                        //Pawn Evolution
                        if ((tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]==6 and tempMove.secondLoc.first==0 and tempMove.flip==1) or (tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]==6 and tempMove.secondLoc.first==7 and tempMove.flip ==-1))
                            tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]=2;

                        if ((tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]==-6 and tempMove.secondLoc.first==7 and tempMove.flip==1) or (tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]==-6 and tempMove.secondLoc.first==0 and tempMove.flip==-1))
                            tempBoard[tempMove.secondLoc.first][tempMove.secondLoc.second]=-2;

                        //evaluate
                        int value=evaluateBoard(tempBoard,flip);
                        if (value<minPoint){
                            minPoint=value;
                            highestMove=tempMove;
                        }
                    }
                }

            }
        }
    }
    return highestMove;
}

#endif // CHESSAI_H
