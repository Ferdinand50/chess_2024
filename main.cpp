#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath> 
#include <vector>
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

	std::vector<Move> legalMoves;

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
						//only accept move is valid piece is selected
						if(gamestate.isPieceTurn(columm, row)){
							moveCoord.xStart = columm;
							moveCoord.yStart = row;
							StartMove = false;
							EndMove = true;
							//TODO: implement a draw highlight function
							}
					}
					else{
						//dont accept same start and end square
						if(moveCoord.xStart !=columm || moveCoord.yStart!=row){
							moveCoord.xEnd = columm;
							moveCoord.yEnd = row;
							StartMove = true;
							EndMove = false;

							// initialize move
							Move move(gamestate.m_chessBoard, moveCoord);
							//Currently buggy
							makeMove(gamestate.m_chessBoard, move);
							//TODO: move this change of turn in the makeMove function
							gamestate.m_whitesTurn = !gamestate.m_whitesTurn;
							std::cout<<moveCoord.xStart<<moveCoord.yStart<<moveCoord.xEnd<<moveCoord.yEnd<<gamestate.m_whitesTurn<<std::endl;

							//update screen
							screen.update(gamestate.m_chessBoard);
						}
					}
			}
		}
		SDL_Delay(floor(32.0f));
	} 
    screen.close();

    return 0;
}