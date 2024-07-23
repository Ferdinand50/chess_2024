#include "gui.h"
#include <iostream>

void drawChessboard(SDL_Renderer *renderer, int SQUARE_SIZE)
{
    bool whiteSquare = true;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            SDL_Rect squareRect = {col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
            if (whiteSquare)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Light color for white square
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Dark color for black square
            }
            SDL_RenderFillRect(renderer, &squareRect);
            whiteSquare = !whiteSquare;
        }
        whiteSquare = !whiteSquare; // Switch color at the end of each row
    }
}

void drawPieces(SDL_Renderer *renderer, int SQUARE_SIZE)
{
    //int chessBoard[8][8]

    //SDL_Surface *surface = IMG_Load( "images/wB.png" ); 
    //SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    
    SDL_Rect destRect = {100, 100, 200, 200}; // Destination rectangle for rendering (x, y, width, height)
    //SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
