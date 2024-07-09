#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gui.h"
#include "gamestate.h"


const int WIDTH = 600, HEIGHT = 600;
const int SQUARE_SIZE = WIDTH / 8;


int main(int argc, char *argv[])
{
    std::cout << "Program started" << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);



    SDL_Window *window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == nullptr or renderer == nullptr)
    {
        std::cout << "Failed to init: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // THIS CODE CRASHED THE PROGRAM
    if(!(IMG_Init(IMG_INIT_PNG) % IMG_INIT_PNG))
    {
        std::cout << "Failed to init SDL_image: " << IMG_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }



  
    bool running = true;
    SDL_Event event;

    // Draw init board
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Background color
    SDL_RenderClear(renderer);
    drawChessboard(renderer, SQUARE_SIZE);
    drawPieces(renderer, SQUARE_SIZE);
    SDL_RenderPresent(renderer);

    while (running)
    {
        while (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Background color
        SDL_RenderClear(renderer);
        drawChessboard(renderer, SQUARE_SIZE);
        drawPieces(renderer, SQUARE_SIZE);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Program terminated" << std::endl;

    return 0;
}
