#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void drawChessboard(SDL_Renderer *renderer, int SQUARE_SIZE);
void drawPieces(SDL_Renderer *renderer, int SQUARE_SIZE);

#endif // GUI_H
