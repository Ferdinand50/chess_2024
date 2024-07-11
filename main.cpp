#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath> 
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

    GameState gamestate;

    bool running = true;
    SDL_Event event;

    // Draw init board
    screen.update(gamestate.m_chessBoard);

	bool QUIT = false;
	while (!QUIT) {

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					QUIT=true;
					break;
			}
		}
		SDL_Delay(floor(32.0f));
	} 

    screen.close();

    return 0;
}