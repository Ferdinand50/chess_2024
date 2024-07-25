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
	int xC;
	int yC;
	MoveCoord moveCoord;

	std::vector<Move> legalMoves;
	getLegalMoves(legalMoves, gamestate);

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
					xC = mx/square;
					yC = my/square;
					if(StartMove){
						//only accept move is valid piece is selected
						if(gamestate.isPieceTurn(xC, yC)){
							moveCoord.xStart = xC;
							moveCoord.yStart = yC;
							StartMove = false;
							EndMove = true;
							//TODO: implement a draw highlight function
							screen.drawHighlights(legalMoves, xC, yC);
							}
					}
					else{
						//dont accept same start and end square
						//TODO: dont accept same color insted 
						if(moveCoord.xStart !=xC || moveCoord.yStart!=yC){
							moveCoord.xEnd = xC;
							moveCoord.yEnd = yC;
							StartMove = true;
							EndMove = false;

							// initialize move
							Move move(gamestate.m_chessBoard, moveCoord);
							if(move.isLegal(legalMoves)){
								std::cout<<"Move is legal"<<std::endl;
							}
							//Currently buggy
							makeMove(gamestate.m_chessBoard, move);
							//TODO: move this change of turn in the makeMove function
							gamestate.m_whitesTurn = !gamestate.m_whitesTurn;
							std::cout<<moveCoord.xStart<<moveCoord.yStart<<moveCoord.xEnd<<moveCoord.yEnd<<gamestate.m_whitesTurn<<std::endl;

							//update screen
							//TODO: unify drawHighlights and update once a timestep
							screen.update(gamestate.m_chessBoard);

							//get legal moves
							getLegalMoves(legalMoves, gamestate);
						}
					}
			}
		}
		SDL_Delay(floor(2.0f));
	} 
	//TODO: Fix segmentation fault while closing
    screen.close();

    return 0;
}