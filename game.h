#include <iostream>
#include <SDL.h>
#include <vector>
#include <SDl_image.h>
#include "struct.h"
#include "rendering.h"
#include "fortest.h"
#include "chessai.h"



#ifndef GAME_H                  //this header include all main game function
#define GAME_H
using namespace std;

struct Game
{
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool turn; // white is 1, black is 0
    int player;//player=0 if 2playermode, player=1 if white player, player-2 if black player
    int menu; // 0 first form,1 is chess1plmode, 2 is chess2plmode

    int Flip; //1 means white view, -1 mean black view

    vector<vector<int>> board;

    void GetMenuInput();
    void Menu();
    Game(){ //constructor
        Flip=1;
        this->board.push_back({-5,-4,-3,-2,-1,-3,-4,-5});
        this->board.push_back({-6,-6,-6,-6,-6,-6,-6,-6});
        this->board.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
        this->board.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
        this->board.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
        this->board.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
        this->board.push_back({ 6, 6, 6, 6, 6, 6, 6, 6});
        this->board.push_back({ 5, 4, 3, 2, 1, 3, 4, 5}); //7
        this->turn=1;
        this->player=0;
        this->menu=0;
        History.push_back(board);


        //init sdl2
        if (SDL_Init(SDL_INIT_EVERYTHING)<0){
            cout << "fail to init " << SDL_GetError();
            exit(0);
        }
        this->window=SDL_CreateWindow("ChessV1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,650,650,SDL_WINDOW_SHOWN);
        this->renderer=SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
        if (!window or !renderer){
            cout << "fail to init window or renderer\n";
            exit(0);
        }
    }
    void PlayChessTwoPl();
    KingAndRockMoveHistory CheckCastle;
    void PlayChessWithAI();
    bool GetMoveInfo(ChessMove &chessmove);
    vector<vector<vector<int>>> History;
    void Move(ChessMove &chessmove);
    void renderBoard();
    void renderFlipBoard();
    void Undo();
    void restartGame();

};

bool Game::GetMoveInfo (ChessMove &chessmove) // Get info when play game include Undo,Restart and Back (optionbar)
{
    static int status=0;                                //when not get firstLoc and secondLoc
    static pair<int,int>firstLoc;
    static pair<int,int>secondLoc;

    if (status==2){
        firstLoc=pair<int,int>(0,0);                    //get both firstLoc and secondLoc
        secondLoc=pair<int,int>(0,0);
        status=0;
    }

    while (SDL_WaitEvent(&(this->event))) {
        Mouse mouse;
        SDL_GetMouseState(&mouse.x,&mouse.y);
        switch (this->event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int j=(mouse.x-37)/73;
                int i=(mouse.y-37)/73;
                if (i>7 or j>7) break;
                cout  << i << " " << j << " " << status <<  endl;
                if (status==0){
                    firstLoc=pair<int,int>(i,j);
                    status=1;
                    if (this->board[firstLoc.first][firstLoc.second]<=0 and this->turn==1)
                        status=0;
                    if (this->board[firstLoc.first][firstLoc.second]>=0 and this->turn==0)
                        status=0;
                    return false;
                }
                else if (status==1){
                    secondLoc=pair<int,int>(i,j);
                    status=2;
                    if (secondLoc==firstLoc){
                        status=0;
                        return false;
                    }
                    chessmove=ChessMove(History,CheckCastle,firstLoc,secondLoc,this->board,board[firstLoc.first][firstLoc.second],this->turn,Flip);
                    return true;
                }
            }
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_h:
                        {
                            drawOptionBoard(renderer);          //open help option
                            SDL_Delay(1000);
                            renderBoard();
                            break;
                        }
                    case SDLK_u:
                        {
                            if (History.size()>1){
                                this->Undo();               //undo
                                renderBoard();
                                cout << turn << endl;
                            }
                            break;
                        }
                    case SDLK_r:
                        {
                            restartGame();                  //restart the game
                            break;
                        }
                    case SDLK_b:
                        {
                            restartGame();                      //restart and back to menu
                            menu=0;
                            break;
                        }
                    case SDLK_f:
                        {
                            Flip=(Flip==1)?-1:1;
                            renderFlipBoard();                  //flip the board
                            break;
                        }
                    }
                    break;
                }
        }
    }
    return false;
}

void Game::Move(ChessMove &chessmove) //  change the board
{
    int i=chessmove.firstLoc.first;
    int j=chessmove.firstLoc.second;
    //CheckCastling update
    if (board[i][j]==1)
        CheckCastle.update(0,0,0,0,0,1);
    else if (board[i][j]==-1)
        CheckCastle.update(0,0,0,0,1,0);
    else if (board[i][j]==5 and ((i==7 and j==0 and Flip==1) or (i==0 and j==7 and Flip==-1)))
        CheckCastle.update(1,0,0,0,0,0);
    else if (board[i][j]==5 and ((i==7 and j==7 and Flip==1) or (i==0 and j==0 and Flip==-1)))
        CheckCastle.update(0,1,0,0,0,0);
    else if (board[i][j]==-5 and ((i==0 and j==7 and Flip==1) or (i==7 and j==0 and Flip==-1)))
        CheckCastle.update(0,0,1,0,0,0);
    else if (board[i][j]==-5 and ((i==0 and j==0 and Flip==1) or (i==7 and j==7 and Flip==-1)))
        CheckCastle.update(0,0,0,1,0,0);
    else CheckCastle.update(0,0,0,0,0,0);

    CheckCastle.printHistoryCastle();


    //for castling
    int dx=0;
    if ((board[chessmove.firstLoc.first][chessmove.firstLoc.second]==1 or board[chessmove.firstLoc.first][chessmove.firstLoc.second]==-1)  and abs(chessmove.secondLoc.second-chessmove.firstLoc.second)==2 and chessmove.firstLoc.first==chessmove.secondLoc.first){
        if (chessmove.secondLoc.second>chessmove.firstLoc.second) dx=1;
        else dx=-1;
        //white
        if (dx>0 and Flip==1 and turn==1){
            board[7][5]=5;
            board[7][7]=0;
        }
        if (dx<0 and Flip==1 and turn==1){
            board[7][3]=5;
            board[7][0]=0;
        }
        if (dx>0 and Flip==-1 and turn==1){
            board[0][4]=5;
            board[0][7]=0;
        }
        if (dx<0 and Flip==-1 and turn==1){
            board[0][2]=5;
            board[0][0]=0;
        }
        //black
        if (dx>0 and Flip==1 and turn==0){
            board[0][5]=-5;
            board[0][7]=0;
        }
        if (dx<0 and Flip==1 and turn==0){
            board[0][3]=-5;
            board[0][0]=0;
        }
        if (dx>0 and Flip==-1 and turn==0){
            board[7][4]=-5;
            board[7][7]=0;
        }
        if (dx<0 and Flip==-1 and turn==0){
            board[7][2]=-5;
            board[7][0]=0;
        }
    }

    //pawn across road case:
    if (abs(board[i][j])==6 and board[i][j-1]==-board[i][j]   //is pawn and the area what to eat is opponent pawn
        and History[History.size()-2][i+2*(turn?-Flip:Flip)][j-1]==-board[i][j]){
            board[i][j-1]=0;
        }
    if (abs(board[i][j])==6 and board[i][j+1]==-board[i][j]   //is pawn and the area what to eat is opponent pawn
        and History[History.size()-2][i+2*(turn?-Flip:Flip)][j+1]==-board[i][j]){
            board[i][j+1]=0;
        }

    //update board
    board[chessmove.secondLoc.first][chessmove.secondLoc.second]=board[chessmove.firstLoc.first][chessmove.firstLoc.second];
    board[chessmove.firstLoc.first][chessmove.firstLoc.second]=0;

    //Pawn Evolution
    if ((board[chessmove.secondLoc.first][chessmove.secondLoc.second]==6 and chessmove.secondLoc.first==0 and chessmove.flip==1)
        or (board[chessmove.secondLoc.first][chessmove.secondLoc.second]==6 and chessmove.secondLoc.first==7 and chessmove.flip ==-1))
        board[chessmove.secondLoc.first][chessmove.secondLoc.second]=2;

    if ((board[chessmove.secondLoc.first][chessmove.secondLoc.second]==-6 and chessmove.secondLoc.first==7 and chessmove.flip==1)
        or (board[chessmove.secondLoc.first][chessmove.secondLoc.second]==-6 and chessmove.secondLoc.first==0 and chessmove.flip==-1))
        board[chessmove.secondLoc.first][chessmove.secondLoc.second]=-2;

    this->History.push_back(board);

    /*
    //say CHECK! if check the opponent's king
    if (chessmove.checkMate()){
        cout << "checkmate\n";
        MessageCheckMate(this->window,turn);
    }else*/
    if (chessmove.Check()){
        cout << "check\n";
        MessageCheck(this->window);
    }

    //update turn and render board
    turn=turn? 0:1;
    cout << turn << endl;
    this->renderBoard();
}

void Game::PlayChessWithAI()
{
    cout << "AI mode\n";
    renderBoard();
    ChessMove chessmove;
    if (turn==1) if (this->GetMoveInfo(chessmove) and chessmove.valid()){
        cout << "move";
        this->board=chessmove.board;
        this->Move(chessmove);
        printChessBoardNum(this->board);

    }
    if (turn==0){
        //chessmove=chooseAIChessMove(History,board,turn,CheckCastle);
        chessmove=simpleAIMove(board,Flip);
        Move(chessmove);
        printChessBoardNum(board);
    }

}

void Game::PlayChessTwoPl()
{
    ChessMove chessmove;
    if (this->GetMoveInfo(chessmove) and chessmove.valid()){
        cout << "move";
        this->board=chessmove.board;
        this->Move(chessmove);
        printChessBoardNum(this->board);

    }
}

void Game::Menu()
{
    while(SDL_PollEvent(&(this->event))) {
        Mouse mouse;
        SDL_GetMouseState(&mouse.x,&mouse.y);

        //menu event
        switch (this->menu)
        {
        case 0:
            {           //when mouse come to a position in menu then change
                if (50<mouse.x and mouse.x<77 and 485<mouse.y and mouse.y<515)
                    loadSecondCase(this->renderer);
                else if (544<mouse.x and mouse.x<580 and 514<mouse.y and mouse.y<558)
                    loadThirdCase(this->renderer);
                else if (mouse.x>525 and mouse.x<598 and mouse.y>60 and mouse.y<116)
                    loadFourthCase(this->renderer);
                else loadFirstCase(this->renderer);
                break;
            }
        case 1:
            {   //chess vs AI
                PlayChessWithAI();
                break;
            }
        case 2:
            {
                //chess 2 pl
                this->PlayChessTwoPl();
            break;

                break;
            }
        case 3: //info
            {
                if (mouse.x>531 and mouse.x<583 and mouse.y>49 and mouse.y<70)
                    loadInfo1(this->renderer);
                else loadInfo(this->renderer);
                break;
            }

        }
        //basic event
        switch(this->event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONDOWN:
            cout << mouse.x << " " << mouse.y << endl;
            if (this->menu==0 and 50<mouse.x and mouse.x<77 and 485<mouse.y and mouse.y<515)
                this->menu=1;
            else if (this->menu==0 and 544<mouse.x and mouse.x<580 and 514<mouse.y and mouse.y<558){
                this->menu=2;
                drawChessBoard(this->renderer);
                this->renderBoard();
            }

            else if (this->menu==0 and mouse.x>525 and mouse.x<598 and mouse.y>60 and mouse.y<116)
                this->menu=3;
            else if (this->menu==3 and mouse.x>531 and mouse.x<583 and mouse.y>49 and mouse.y<70)
                this->menu=0;
            break;



        default:
            break;
        }

    }
}

void Game::renderBoard()
{
    drawChessBoard(this->renderer);
    vector<ChessPiece> x;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (this->board[i][j]!=0)
                x.push_back(ChessPiece(i,j,board[i][j]));
        }
    }

    for (unsigned int i=0;i<x.size();i++){
        drawChessPiece(x[i],this->renderer);
    }
    SDL_RenderPresent(this->renderer);
}

void Game::renderFlipBoard()
{
    vector<vector<int>> board_=board;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            board[7-i][7-j]=board_[i][j];
        }
    }
    renderBoard();
}

void Game::Undo()       //change History and KingAndRockHistory and the board too
{

        vector<vector<vector<int>>> history_(History.size()-1,vector<vector<int>>(8,vector<int>(8,0)));
        for (unsigned int i=0;i<History.size()-1;i++){
            history_[i]=History[i];
        }
        History=history_;
        board=history_[history_.size()-1];
        turn=turn?0:1;

        //undo kingrock history
        int HistoryLength=CheckCastle.BlackKing.size();
        if (HistoryLength>1){
            CheckCastle.BlackKing.erase(CheckCastle.BlackKing.begin()+HistoryLength-1,CheckCastle.BlackKing.begin()+HistoryLength);
            CheckCastle.WhiteKing.erase(HistoryLength-1+CheckCastle.WhiteKing.begin(),HistoryLength+CheckCastle.WhiteKing.begin());
            CheckCastle.LeftBlackRock.erase(HistoryLength-1+CheckCastle.LeftBlackRock.begin(),HistoryLength+CheckCastle.LeftBlackRock.begin());
            CheckCastle.LeftWhiteRock.erase(HistoryLength-1+CheckCastle.LeftWhiteRock.begin(),HistoryLength+CheckCastle.LeftWhiteRock.begin());
            CheckCastle.RightBlackRock.erase(HistoryLength-1+CheckCastle.RightBlackRock.begin(),HistoryLength+CheckCastle.RightBlackRock.begin());
            CheckCastle.RightWhiteRock.erase(HistoryLength-1+CheckCastle.RightWhiteRock.begin(),HistoryLength+CheckCastle.RightWhiteRock.begin());
        }


}

void Game::restartGame()    //Restart all properties
{
    vector<vector<vector<int>>> history_;
    History=history_;
    vector<vector<int>> board_;
    board_.push_back({-5,-4,-3,-2,-1,-3,-4,-5});
    board_.push_back({-6,-6,-6,-6,-6,-6,-6,-6});
    board_.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
    board_.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
    board_.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
    board_.push_back({ 0, 0, 0, 0, 0, 0, 0, 0});
    board_.push_back({ 6, 6, 6, 6, 6, 6, 6, 6});
    board_.push_back({ 5, 4, 3, 2, 1, 3, 4, 5}); //7
    turn=1;
    Flip=1;
    player=0;
    menu=2;

    //restart KingRock history
    CheckCastle=KingAndRockMoveHistory();

    History.push_back(board_);
    board=board_;
    renderBoard();

}
#endif // GAME_H
