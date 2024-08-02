#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <iostream>
#include "Movement.h"
#include "gamestate.h"
#include <map>


using namespace std;


class Screen {
public:
    const static int SCREEN_WIDTH = 600;
    std::unordered_map<int, int> m_pieceToImageIndex = {
        {12, 0}, {13, 1}, {14, 2},
        {15, 3}, {16, 4}, {11, 5},
        {22, 6}, {23, 7}, {24, 8},
        {25, 9}, {26, 10}, {21, 11}
    };
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture; 
    SDL_Surface * m_images[12];
    SDL_Rect m_rect;
    SDL_Texture* m_boardTexture;
    

public:
    Screen();
    bool init();
    //update the screen after each game move
    void update(const GameState &gamestate, const std::vector<Move> &legalMoves, int x, int y, bool b_drawHighlights);
    //draws the board
    void draw_board();
    //draw possile moves of a piece
    void drawHighlights(const std::vector<Move> &legalMoves, int x, int y);
    //draw pieces on the board
    void draw_pieces(const GameState &gamestate);
    //precompute the 8x8 chess board
    void precomputeBoard();
    void close();
};


#endif // SCREEN_H