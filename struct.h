#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdlib.h>
#ifndef STRUCT_H        //this header include struct mouse for SDL Mouse, ChessPiece and ChessMove with KingAndRockHistory
#define STRUCT_H            //to check castling case

using namespace std;

struct ChessPiece
{
    vector <pair<int,int>> SquareCanMove;
    pair<int,int> myLocation; //vi tri cua quan co mang kep
    int value; // gia tri quan co de sau nay tinh diem the co
    void updateValue();
    int type; // phan biet cac quan co
    ChessPiece(){
        this->myLocation.first=10; //x
        this->myLocation.second=10; //y
    }
    void UpdateSquareCanMove(const vector<vector<int>>& board,const int flip);
    void GetSquareCanMove();
    ChessPiece(int i,int j,int type_){
        this->type=type_;
        this->myLocation.first=i;
        this->myLocation.second=j;
    }

};

void ChessPiece::updateValue()
{
    switch(type)
    {
    case 1:
        value=1000;
        break;
    case 2:
        value=90;
        break;
    case 3:
        value=30;
        break;
    case 4:
        value=30;
        break;
    case 5:
        value =50;
        break;
    case 6:
        value=10;
        break;
    case -1:
        value=-1000;
        break;
    case -2:
        value=-90;
        break;
    case -3:
        value=-30;
        break;
    case -4:
        value=-30;
        break;
    case -5:
        value =-50;
        break;
    case -6:
        value=-10;
        break;
    }
}

void ChessPiece::UpdateSquareCanMove(const vector<vector<int>>& board,const int flip)
{
    pair<int,int> Loc=this->myLocation;
    switch (type)
    {
    case 1://white king
    {
        if (Loc.first-1>=0 and board[Loc.first-1][Loc.second]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first-1,Loc.second));
        if (Loc.first+1<=7 and board[Loc.first+1][Loc.second]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first+1,Loc.second));
        if (Loc.second-1>=0 and board[Loc.first][Loc.second-1]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first,Loc.second-1));
        if (Loc.second+1<=7 and board[Loc.first][Loc.second+1]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first,Loc.second+1));

        if (Loc.second+1<=7 and Loc.first+1<8 and board[Loc.first+1][Loc.second+1]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first+1,Loc.second+1));
        if (Loc.second+1<=7 and Loc.first-1>=0 and board[Loc.first-1][Loc.second+1]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first-1,Loc.second+1));
        if (Loc.second-1>=0 and Loc.first-1>=0 and board[Loc.first-1][Loc.second-1]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first-1,Loc.second-1));
        if (Loc.second-1>=0 and Loc.first+1<8 and board[Loc.first+1][Loc.second-1]<=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first+1,Loc.second-1));

        //castling case:

        break;
    }

    case -1: //black king
    {

        if (Loc.first-1>=0 and board[Loc.first-1][Loc.second]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first-1,Loc.second));
        if (Loc.first+1<=7 and board[Loc.first+1][Loc.second]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first+1,Loc.second));
        if (Loc.second-1>=0 and board[Loc.first][Loc.second-1]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first,Loc.second-1));
        if (Loc.second+1<=7 and board[Loc.first][Loc.second+1]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first,Loc.second+1));

        if (Loc.second+1<=7 and Loc.first+1<8 and board[Loc.first+1][Loc.second+1]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first+1,Loc.second+1));
        if (Loc.second+1<=7 and Loc.first-1>=0 and board[Loc.first-1][Loc.second+1]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first-1,Loc.second+1));
        if (Loc.second-1>=0 and Loc.first-1>=0 and board[Loc.first-1][Loc.second-1]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first-1,Loc.second-1));
        if (Loc.second-1>=0 and Loc.first+1<8 and board[Loc.first+1][Loc.second-1]>=0)
            this->SquareCanMove.push_back(pair<int,int>(Loc.first+1,Loc.second-1));
        break;
    }

    case 2: //white queen
    {
        int i=Loc.first,j=Loc.second;
        while(true){
            i--;
            if (i<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i++;
            if (i>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            j++;
            if (j>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            j--;
            if (j<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i++;j++;
            if (i>7 or j>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i++;j--;
            if (i>7 or j<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i--;j++;
            if (i<0 or j>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i--;j--;
            if (i<0 or j<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }
        break;
    }

    case -2://black queen
    {
        int i_=Loc.first,j_=Loc.second;
        while(true){
            i_--;
            if (i_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_++;
            if (i_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            j_++;
            if (j_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            j_--;
            if (j_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_++;j_++;
            if (i_>7 or j_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_++;j_--;
            if (i_>7 or j_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_--;j_++;
            if (i_<0 or j_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_--;j_--;
            if (i_<0 or j_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }
        break;
    }

    case 3://white bishop
    {
        int i=Loc.first,j=Loc.second;
        while(true){
            i++;j++;
            if (i>7 or j>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i++;j--;
            if (i>7 or j<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i--;j++;
            if (i<0 or j>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i--;j--;
            if (i<0 or j<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }
        break;
    }

    case -3://black bishop
    {
        int i_=Loc.first,j_=Loc.second;
        while(true){
            i_++;j_++;
            if (i_>7 or j_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_++;j_--;
            if (i_>7 or j_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_--;j_++;
            if (i_<0 or j_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_--;j_--;
            if (i_<0 or j_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }
        break;
    }

    case 4: //white knight
    {
        int i=Loc.first,j=Loc.second;
        if (i+2<=7 and j+1<=7 and board[i+2][j+1]<=0)
            SquareCanMove.push_back(pair<int,int>(i+2,j+1));
        if (i+2<=7 and j-1>=0 and board[i+2][j-1]<=0)
            SquareCanMove.push_back(pair<int,int>(i+2,j-1));
        if (i-2>=0 and j-1>=0 and board[i-2][j-1]<=0)
            SquareCanMove.push_back(pair<int,int>(i-2,j-1));
        if (i-2>=0 and j+1<=7 and board[i-2][j+1]<=0)
            SquareCanMove.push_back(pair<int,int>(i-2,j+1));

        if (i+1<=7 and j+2<=7 and board[i+1][j+2]<=0)
            SquareCanMove.push_back(pair<int,int>(i+1,j+2));
        if (i+1<=7 and j-2>=0 and board[i+1][j-2]<=0)
            SquareCanMove.push_back(pair<int,int>(i+1,j-2));
        if (i-1>=0 and j-2>=0 and board[i-1][j-2]<=0)
            SquareCanMove.push_back(pair<int,int>(i-1,j-2));
        if (i-1>=0 and j+2<=7 and board[i-1][j+2]<=0)
            SquareCanMove.push_back(pair<int,int>(i-1,j+2));
        break;
    }

    case -4: //black knight
    {
        int i=Loc.first,j=Loc.second;
        if (i+2<=7 and j+1<=7 and board[i+2][j+1]>=0)
            SquareCanMove.push_back(pair<int,int>(i+2,j+1));
        if (i+2<=7 and j-1>=0 and board[i+2][j-1]>=0)
            SquareCanMove.push_back(pair<int,int>(i+2,j-1));
        if (i-2>=0 and j-1>=0 and board[i-2][j-1]>=0)
            SquareCanMove.push_back(pair<int,int>(i-2,j-1));
        if (i-2>=0 and j+1<=7 and board[i-2][j+1]>=0)
            SquareCanMove.push_back(pair<int,int>(i-2,j+1));

        if (i+1<=7 and j+2<=7 and board[i+1][j+2]>=0)
            SquareCanMove.push_back(pair<int,int>(i+1,j+2));
        if (i+1<=7 and j-2>=0 and board[i+1][j-2]>=0)
            SquareCanMove.push_back(pair<int,int>(i+1,j-2));
        if (i-1>=0 and j-2>=0 and board[i-1][j-2]>=0)
            SquareCanMove.push_back(pair<int,int>(i-1,j-2));
        if (i-1>=0 and j+2<=7 and board[i-1][j+2]>=0)
            SquareCanMove.push_back(pair<int,int>(i-1,j+2));
        break;
    }

    case 5: //white rock
    {
        int i=Loc.first,j=Loc.second;
        while(true){
            i--;
            if (i<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            i++;
            if (i>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            j++;
            if (j>7 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }

        i=Loc.first,j=Loc.second;
        while(true){
            j--;
            if (j<0 or board[i][j]>0) break;
            this->SquareCanMove.push_back(pair<int,int>(i,j));
            if (board[i][j]<0) break;
        }
        break;
    }

    case -5: //black rock
    {
        int i_=Loc.first,j_=Loc.second;
        while(true){
            i_--;
            if (i_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            i_++;
            if (i_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            j_++;
            if (j_>7 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }

        i_=Loc.first,j_=Loc.second;
        while(true){
            j_--;
            if (j_<0 or board[i_][j_]<0) break;
            this->SquareCanMove.push_back(pair<int,int>(i_,j_));
            if (board[i_][j_]>0) break;
        }
        break;
    }

    case 6: //white pawn: 3 special rules
    {
        int i=Loc.first,j=Loc.second;

        //pawn eat
        if (board[i-flip][j+1]<0)
            SquareCanMove.push_back(pair<int,int>(i-flip,j+1));
        if (board[i-flip][j-1]<0)
            SquareCanMove.push_back(pair<int,int>(i-flip,j-1));

        //pawn first move
        bool flag=0;
        if (i==6 or i==1){
            if (board[i-flip][j]==0){
                SquareCanMove.push_back(pair<int,int>(i-flip,j));
                flag=1;
            }
            if (flag==1){
                flag=0;
                if (board[i-2*flip][j]==0)
                    SquareCanMove.push_back(pair<int,int>(i-2*flip,j));
            }
            break;
        }

        //pawn normal move
        if (board[i-flip][j]==0){
            SquareCanMove.push_back(pair<int,int>(i-flip,j));
        }
        break;

    }

    case -6://black pawn
    {
        int i=Loc.first,j=Loc.second;

        //pawn eat
        if (board[i+flip][j+1]>0)
            SquareCanMove.push_back(pair<int,int>(i+flip,j+1));
        if (board[i+flip][j-1]>0)
            SquareCanMove.push_back(pair<int,int>(i+flip,j-1));

        //pawn first move
        bool flag=0;
        if (i==6 or i==1){
            if (board[i+flip][j]==0){
                SquareCanMove.push_back(pair<int,int>(i+flip,j));
                flag=1;
            }
            if (flag==1){
                flag=0;
                if (board[i+2*flip][j]==0)
                    SquareCanMove.push_back(pair<int,int>(i+2*flip,j));
            }
            break;
        }

        //pawn normal move
        if (board[i+flip][j]==0){
            SquareCanMove.push_back(pair<int,int>(i+flip,j));
        }
        break;
    }
    }
}

void ChessPiece::GetSquareCanMove()
{
    for (unsigned int i=0;i<this->SquareCanMove.size();i++){
        cout << SquareCanMove[i].first << " " << SquareCanMove[i].second << endl;
    }
}


struct KingAndRockMoveHistory // used to check for castling
{
    vector <bool> LeftWhiteRock;
    vector<bool> RightWhiteRock;
    vector<bool> LeftBlackRock;
    vector<bool> RightBlackRock;

    vector<bool> BlackKing;
    vector<bool> WhiteKing;
    void update(bool LeftWhiteRock_,bool RightWhiteRock_,bool LeftBlackRock_,bool RightBlackRock_,bool BlackKing_,bool WhiteKing_);
    KingAndRockMoveHistory() //restart
    {
        vector<bool> x(1,0);
        LeftBlackRock=x;
        RightBlackRock=x;
        LeftWhiteRock=x;
        RightWhiteRock=x;
        BlackKing=x;
        WhiteKing=x;
    }
    void printHistoryCastle();
};

void KingAndRockMoveHistory::update(bool LeftWhiteRock_,bool RightWhiteRock_,bool LeftBlackRock_,bool RightBlackRock_,bool BlackKing_,bool WhiteKing_)
{
    LeftBlackRock.push_back(LeftBlackRock_ or LeftBlackRock[LeftBlackRock.size()-1]);
    LeftWhiteRock.push_back(LeftWhiteRock_ or LeftWhiteRock[LeftWhiteRock.size()-1]);
    RightWhiteRock.push_back(RightWhiteRock_ or RightWhiteRock[RightWhiteRock.size()-1]);
    RightBlackRock.push_back(RightBlackRock_ or RightBlackRock[RightBlackRock.size()-1]);
    BlackKing.push_back(BlackKing_ or BlackKing[BlackKing.size()-1]);
    WhiteKing.push_back(WhiteKing_ or WhiteKing[WhiteKing.size()-1]);
}

void KingAndRockMoveHistory::printHistoryCastle()
{
    for (unsigned int i=0;i<WhiteKing.size();i++)
        cout << " LeftWhiteRock: " << LeftWhiteRock[i] << " LeftBlackRock: " << LeftBlackRock[i] << " RightBlackRock: " << RightBlackRock[i] << " RightWhiteRock: " << RightWhiteRock[i] << " White King:  " << WhiteKing[i] << " black king: " << BlackKing[i] << endl;
}

struct Mouse
{
    int x;
    int y;
};

struct ChessMove
{
    bool turn;
    int flip;
    bool UpdateKingCheck(); //1 is white king, 0 is no check and -1 is black king
    pair<int,int> firstLoc;
    pair<int,int> secondLoc;
    vector<vector<int>> board;
    KingAndRockMoveHistory CheckCastle;
    vector<vector<vector<int>>> History;
    int type; // the type of the piece moved
    bool valid();
    bool Check();
    bool checkMate();
    ChessMove()
    {
        this->type=0;
        flip=1;
    }
    ChessMove(vector<vector<vector<int>>> History_,KingAndRockMoveHistory CheckCastle_,
              pair<int,int> firstLoc_,pair<int,int> secondLoc_,vector<vector<int>> board_,int type_,bool turn_=0,int flip_=1)
    {
        firstLoc=firstLoc_;
        secondLoc=secondLoc_;
        board=board_;
        type=type_;
        turn=turn_;
        flip=flip_;
        CheckCastle=CheckCastle_;
        History=History_;
    }
};

bool ChessMove::valid() // check if move is valid or not
{
    ChessPiece piece(this->firstLoc.first,this->firstLoc.second,this->type);
    if (turn==1 and this->board[firstLoc.first][firstLoc.second]<=0) return false;
    if (turn==0 and this->board[firstLoc.first][firstLoc.second]>=0) return false;
    piece.UpdateSquareCanMove(this->board,flip);

    //castle case:
    bool ableToCastle=0;
    int dx;
    if ((board[firstLoc.first][firstLoc.second]==1 or board[firstLoc.first][firstLoc.second]==-1)  and abs(secondLoc.second-firstLoc.second)==2 and firstLoc.first==secondLoc.first){
        if (secondLoc.second>firstLoc.second) dx=1;
        else dx=-1;

        cout << "castle case 1" << endl;
        if (board[firstLoc.first][firstLoc.second+dx]==0 and board[secondLoc.first][secondLoc.second]==0 ){
            //check white king and right white rock
            if ((dx>0 and turn==1 and flip==1) or (dx<0 and turn ==1 and flip==-1)){
                if (CheckCastle.WhiteKing[CheckCastle.WhiteKing.size()-1]==0 and CheckCastle.RightWhiteRock[CheckCastle.RightWhiteRock.size()-1]==0)
                    ableToCastle=1;
            }

            //check white king and left white rock
            if (((dx<0 && turn && flip==1) or  (dx>0 && turn && flip==-1)) && board[secondLoc.first][secondLoc.second+dx]==0){
                if (CheckCastle.WhiteKing[CheckCastle.WhiteKing.size()-1]==0 and CheckCastle.LeftWhiteRock[CheckCastle.LeftWhiteRock.size()-1]==0)
                    ableToCastle=1;
            }

            //check black king and right black rock
            if (((dx<0 and turn==0 and flip==1) or (dx>0 and turn ==0 and flip==-1))and board[secondLoc.first][secondLoc.second+dx]==0){
                if (CheckCastle.BlackKing[CheckCastle.BlackKing.size()-1]==0 and CheckCastle.LeftBlackRock[CheckCastle.LeftBlackRock.size()-1]==0)
                    ableToCastle=1;
            }

            //check black king and left black rock
            if ((dx>0 and turn==0 and flip==1) or (dx<0 and turn ==0 and flip==-1) ){
                if (CheckCastle.BlackKing[CheckCastle.BlackKing.size()-1]==0 and CheckCastle.RightBlackRock[CheckCastle.RightBlackRock.size()-1]==0)
                    ableToCastle=1;
            }
        }
    }
    if (ableToCastle==1 and UpdateKingCheck()==1 ){
        ChessMove x=ChessMove(History,CheckCastle,firstLoc,pair<int,int>(firstLoc.first,firstLoc.second+dx),board,turn,flip);
        if (x.UpdateKingCheck()) return true;
    }

    //pawn across road case:
    if (abs(board[firstLoc.first][firstLoc.second])==6 and board[firstLoc.first][firstLoc.second-1]==-board[firstLoc.first][firstLoc.second]   //is pawn and the area what to eat is opponent pawn
        and History[History.size()-2][firstLoc.first+2*(turn?-flip:flip)][firstLoc.second-1]==-board[firstLoc.first][firstLoc.second]){

            cout << "pawn across road case \n";
            piece.SquareCanMove.push_back(pair<int,int>(firstLoc.first+(turn? -flip:flip),firstLoc.second-1));
        }
    if (abs(board[firstLoc.first][firstLoc.second])==6 and board[firstLoc.first][firstLoc.second+1]==-board[firstLoc.first][firstLoc.second]   //is pawn and the area what to eat is opponent pawn
        and History[History.size()-2][firstLoc.first+2*(turn?-flip:flip)][firstLoc.second+1]==-board[firstLoc.first][firstLoc.second]){

            cout << "pawn across road case \n";
            piece.SquareCanMove.push_back(pair<int,int>(firstLoc.first+(turn? -flip:flip),firstLoc.second+1));
        }

    //normal case:
    bool IsValid=0;
    for (unsigned int i=0;i<piece.SquareCanMove.size();i++){
        if (piece.SquareCanMove[i]==secondLoc)
            IsValid=1;
    }
    return (IsValid and this->UpdateKingCheck());
}

bool ChessMove::UpdateKingCheck()
{
    vector<vector<int>> board_=this->board;
    board_[secondLoc.first][secondLoc.second]=board_[firstLoc.first][firstLoc.second];
    board_[firstLoc.first][firstLoc.second]=0;

    vector<ChessPiece> piece;
    pair<int,int> KingPosit;

    if (this->turn==1){
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                if (board_[i][j]==1) KingPosit=pair<int,int>(i,j);
                if (board_[i][j]<0) piece.push_back(ChessPiece(i,j,board_[i][j]));
            }
        }
        for (unsigned int i=0;i<piece.size();i++){
            piece[i].UpdateSquareCanMove(board_,flip);
            for (unsigned int j=0;j<piece[i].SquareCanMove.size();j++){
                if (piece[i].SquareCanMove[j]==KingPosit) return false;
            }
        }
    }
    if (this->turn==0){
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                if (board_[i][j]==-1) KingPosit=pair<int,int>(i,j);
                if (board_[i][j]>0) piece.push_back(ChessPiece(i,j,board_[i][j]));
            }
        }
        for (unsigned int i=0;i<piece.size();i++){
            piece[i].UpdateSquareCanMove(board_,flip);
            for (unsigned int j=0;j<piece[i].SquareCanMove.size();j++){
                if (piece[i].SquareCanMove[j]==KingPosit) return false;
            }
        }
    }
    return true;
}

bool ChessMove::Check()
{
    vector<vector<int>> board_=this->board;
    board_[secondLoc.first][secondLoc.second]=board_[firstLoc.first][firstLoc.second];
    board_[firstLoc.first][firstLoc.second]=0;

    //Pawn Evolution
    if ((board_[secondLoc.first][secondLoc.second]==6 and secondLoc.first==0 and flip==1) or
         (board_[secondLoc.first][secondLoc.second]==6 and secondLoc.first==7 and flip==-1))
        board_[secondLoc.first][secondLoc.second]=2;

    if ((board_[secondLoc.first][secondLoc.second]==-6 and secondLoc.first==7 and flip==1) or
         (board_[secondLoc.first][secondLoc.second]==-6 and secondLoc.first==0 and flip==-1))
        board_[secondLoc.first][secondLoc.second]=-2;

    vector<ChessPiece> piece;
    pair<int,int> KingPosit;

    if (this->turn==1){
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                if (board_[i][j]==-1) KingPosit=pair<int,int>(i,j);
                if (board_[i][j]>0) piece.push_back(ChessPiece(i,j,board_[i][j]));
            }
        }
        for (unsigned int i=0;i<piece.size();i++){
            piece[i].UpdateSquareCanMove(board_,flip);
            for (unsigned int j=0;j<piece[i].SquareCanMove.size();j++){
                if (piece[i].SquareCanMove[j]==KingPosit) return true;
            }
        }
    }

    if (this->turn==0){
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                if (board_[i][j]==1) KingPosit=pair<int,int>(i,j);
                if (board_[i][j]<0) piece.push_back(ChessPiece(i,j,board_[i][j]));
            }
        }
        for (unsigned int i=0;i<piece.size();i++){
            piece[i].UpdateSquareCanMove(board_,flip);
            for (unsigned int j=0;j<piece[i].SquareCanMove.size();j++){
                if (piece[i].SquareCanMove[j]==KingPosit) return true;
            }
        }
    }
    return false;
}

bool ChessMove::checkMate()
{
    if (this->Check()==0) return false;
    vector<vector<int>> board_=board;

    board_[secondLoc.first][secondLoc.second]=board_[firstLoc.first][firstLoc.second];
    board_[firstLoc.first][firstLoc.second]=0;

    //Pawn Evolution
    if ((board_[secondLoc.first][secondLoc.second]==6 and secondLoc.first==0 and flip==1) or
         (board_[secondLoc.first][secondLoc.second]==6 and secondLoc.first==7 and flip==-1))
        board_[secondLoc.first][secondLoc.second]=2;

    if ((board_[secondLoc.first][secondLoc.second]==-6 and secondLoc.first==7 and flip==1) or
         (board_[secondLoc.first][secondLoc.second]==-6 and secondLoc.first==0 and flip==-1))
        board_[secondLoc.first][secondLoc.second]=-2;

    turn=turn?0:1;

    vector<ChessPiece> piece; //vector to store opponent's piece
    pair<int,int> KingPosit; //vector to save opponent's king 's location

    if (this->turn==1){
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                if (board_[i][j]==-1) KingPosit=pair<int,int>(i,j);
                if (board_[i][j]<0) piece.push_back(ChessPiece(i,j,board_[i][j]));
            }
        }
        for (unsigned int i=0;i<piece.size();i++){
            piece[i].UpdateSquareCanMove(board_,flip);

            for (unsigned int j=0;j<piece[i].SquareCanMove.size();j++){
                ChessMove thisMove=ChessMove(History,CheckCastle,piece[i].myLocation,piece[i].SquareCanMove[j],board_,board_[piece[i].myLocation.first][piece[i].myLocation.second],turn,flip);
                if (thisMove.valid()) return false;     //if there a move valid then return false
            }
        }
    }


    if (this->turn==0){
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                if (board_[i][j]==1) KingPosit=pair<int,int>(i,j);
                if (board_[i][j]>0) piece.push_back(ChessPiece(i,j,board_[i][j]));
            }
        }
        for (unsigned int i=0;i<piece.size();i++){
            piece[i].UpdateSquareCanMove(board_,flip);


            for (unsigned int j=0;j<piece[i].SquareCanMove.size();j++){
                ChessMove thisMove=ChessMove(History,CheckCastle,piece[i].myLocation,piece[i].SquareCanMove[j],board_,board_[piece[i].myLocation.first][piece[i].myLocation.second],0);
                if (thisMove.valid()) return false;
            }
        }
    }

    return true;
}



#endif

