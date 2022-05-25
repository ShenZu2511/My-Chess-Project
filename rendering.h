
#include <iostream>
#include <SDL.h>
#include <vector>
#include <SDl_image.h>
#include "struct.h"

#ifndef RENDERING_H                 //include base function to render game
#define RENDERING_H
using namespace std;

void drawChessPiece(ChessPiece& chesspiece,SDL_Renderer* renderer)
{
    SDL_Texture* image;
    SDL_Rect rect;
    switch (chesspiece.type)
    {
    case 2:
        image=IMG_LoadTexture(renderer,"whitequeen.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case -2:
        image=IMG_LoadTexture(renderer,"blackqueen.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case 1:
        image=IMG_LoadTexture(renderer,"whiteking.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case -1:
        image=IMG_LoadTexture(renderer,"blackking.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case 3:
        image=IMG_LoadTexture(renderer,"whitebishop.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case -3:
        image=IMG_LoadTexture(renderer,"blackbishop.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case 4:
        image=IMG_LoadTexture(renderer,"whiteknight.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case -4:
        image=IMG_LoadTexture(renderer,"blackknight.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case 5:
        image=IMG_LoadTexture(renderer,"whiterock.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case -5:
        image=IMG_LoadTexture(renderer,"blackrock.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case 6:
        image=IMG_LoadTexture(renderer,"whitepawn.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;

    case -6:
        image=IMG_LoadTexture(renderer,"blackpawn.png");
        rect.h=72;
        rect.w=69;
        rect.x=37+73*chesspiece.myLocation.second;
        rect.y=37+73*chesspiece.myLocation.first;
        SDL_RenderCopy(renderer,image,NULL,&rect);
        break;


    }
}


void initSDL2(SDL_Renderer* renderer,SDL_Window* window)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)<0){
        cout << "fail to init " << SDL_GetError();
        exit(0);
    }
    window=SDL_CreateWindow("ChessV1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,650,650,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (!window or !renderer){
        cout << "fail to init window or renderer\n";
        exit(0);
    }

}

void drawChessBoard(SDL_Renderer* renderer)
{
    SDL_Texture* image=NULL;
    image=IMG_LoadTexture(renderer,"chessboard.png");
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_RenderPresent(renderer);
}

//menu effects
void loadFirstCase(SDL_Renderer* renderer)
{
    SDL_Texture *image;
    image=IMG_LoadTexture(renderer,"chesslogopart3.0.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_DestroyTexture(image);

}
void loadSecondCase(SDL_Renderer* renderer)
{
    SDL_Texture* image;
    image=IMG_LoadTexture(renderer,"chesslogopart3.2.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_DestroyTexture(image);
}
void loadThirdCase(SDL_Renderer* renderer)
{
    SDL_Texture* image;
    image=IMG_LoadTexture(renderer,"chesslogopart3.3.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_DestroyTexture(image);
}
void loadFourthCase(SDL_Renderer* renderer)
{
    SDL_Texture* image;
    image=IMG_LoadTexture(renderer,"chesslogopart3.1.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_DestroyTexture(image);
}

void loadInfo(SDL_Renderer* renderer)
{
    SDL_Texture* image;
    image=IMG_LoadTexture(renderer,"chessinfo.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_DestroyTexture(image);
}

void loadInfo1(SDL_Renderer* renderer)
{
    SDL_Texture* image;
    image=IMG_LoadTexture(renderer,"chessinfo1.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,NULL);
    SDL_DestroyTexture(image);
}


void drawOptionBoard(SDL_Renderer* renderer)
{
    SDL_Texture* image;
    SDL_Rect rect;
    rect.x=200;
    rect.y=200;
    rect.h=300;
    rect.w=300;
    image=IMG_LoadTexture(renderer,"option.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,image,NULL,&rect);
    SDL_RenderPresent(renderer);
}

void MessageCheck(SDL_Window* window)
{
    //SDL_Window* window;
    //window=SDL_CreateWindow("check",100,100,100,100,SDL_WINDOW_SHOWN);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Info","CHECK!",window);
}

void MessageCheckMate(SDL_Window* window,bool turn)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Info",turn?"CHECKMATE! WHITE WON!\nPress R to restart...":"CHECKMATE! BLACKWON!\nPress R to restart...",window);
}
#endif // RENDERING_H

