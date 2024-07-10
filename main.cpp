#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "screen.h"
#include "gamestate.h"


const int WIDTH = 600, HEIGHT = 600;
const int SQUARE_SIZE = WIDTH / 8;


int main(int argc, char *argv[])
{
	Screen screen;
	if(screen.init()==false){
		cout<<"Error initalising SDL."<<endl;
		return 1;
	}
  
    bool running = true;
    SDL_Event event;

    // Draw init board
    screen.update();

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

        screen.update();
    }

    screen.close();

    return 0;
}