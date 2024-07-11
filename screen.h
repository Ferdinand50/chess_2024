#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <unordered_map>

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

    // bool m_second_click;
    // int m_current_click[2];
    // int m_previous_click[2];
    

public:
    Screen();
    bool init();
    void update(int board[8][8]);
    void draw_board();
    void draw_pieces(int board[8][8]);
    // bool processEvents();
    void close();
};


#endif // SCREEN_H