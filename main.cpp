#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath> 
#include "screen.h"
#include "gamestate.h"
#include "Movement.h"

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
	bool StartMove =true;
	bool EndMove = false;
	int mx;
	int my;
	int square = screen.SCREEN_WIDTH/8;
	int row;
	int columm;
	MoveCoord moveCoord;

    // Draw init board
    screen.update(gamestate.m_chessBoard);

	bool QUIT = false;
	while (!QUIT) {

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					QUIT=true;
					break;
				//move pieves via mouse clicks
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mx,&my);
					row = mx/square;
					columm = my/square;
					if(StartMove){
						moveCoord.xStart = row;
						moveCoord.yStart = columm;
						StartMove = false;
						EndMove = true;
						//screen.draw_hightlight(gamestate.m_bitboards);
					}
					else{
						moveCoord.xEnd = row;
						moveCoord.yEnd = columm;
						StartMove = true;
						EndMove = false;

						// initialize move
						Move move(gamestate.m_chessBoard, moveCoord);
						//Currently buggy
						makeMove(&gamestate.m_chessBoard, move);
						std::cout<<moveCoord.xStart<<moveCoord.yStart<<moveCoord.xEnd<<moveCoord.yEnd<<std::endl;

						//update screen
						 screen.update(gamestate.m_chessBoard);
					}
			}
		}
		SDL_Delay(floor(32.0f));
	} 
    screen.close();

    return 0;
}