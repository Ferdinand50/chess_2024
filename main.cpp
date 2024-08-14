#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath> 
#include <vector>
#include <string.h>
#include "screen.h"
#include "gamestate.h"
#include "Movement.h"
#include "opponent.h"


int main(int argc, char *argv[])
{
	//TODO: there seems to be a back which moves pieces sometimes (more investigation needed)
	//TODO: suddenly spawn queens need fix
	Screen screen;
	if(screen.init()==false){
		cout<<"Error initialising SDL."<<endl;
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

	bool gameover = false;
    bool WhiteHuman = true;
    bool BlackHuman = false;
	bool humanTurn;
	// bool moveMade = false;
	//handles AI moves
	AI_Handler handler_AI_moves;

	std::vector<Move> legalMoves;
	std::vector<Move> theoreticalMoves;
	getLegalMoves(legalMoves, theoreticalMoves, gamestate);

    // Draw init board
    screen.update(gamestate, legalMoves, xC, yC, false);

	bool QUIT = false;
	while (!QUIT) {
		humanTurn = (gamestate.m_whitesTurn and WhiteHuman) || (!gamestate.m_whitesTurn and BlackHuman);
		//TODO: does PollEvent work like intended? 
		//maybe runs code whenever an event occurs 
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					QUIT=true;
					break;
				//move pieces via mouse clicks
				case SDL_MOUSEBUTTONDOWN:
                    //only can make moves if game is not over or players turn
                    if (!gameover and humanTurn){
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
								}
						}
						else {
							//dont accept same start and end square
							if(moveCoord.xStart !=xC || moveCoord.yStart!=yC){
								moveCoord.xEnd = xC;
								moveCoord.yEnd = yC;
								StartMove = true;
								EndMove = false;

								// initialize move
								Move move(gamestate, moveCoord);
								if(move.isLegal(legalMoves)){
									//make the move
									makeMove(gamestate, move);
									//update legal moves
									getLegalMoves(legalMoves, theoreticalMoves, gamestate);
								// deselect initial piece and select new one of same color
								} else if(gamestate.isPieceTurn(xC, yC)){
									moveCoord.xStart = xC;
									moveCoord.yStart = yC;
									StartMove = false;
									EndMove = true;
								}
							}
						}
					}

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_z) {
						undoMove(gamestate);
					}
				//TODO: case reset game
			}
		}

		//AI Moves
		if(!gameover && !humanTurn){
			Move opponentMove;
			// get best AI move from legal moves
			opponentMove = handler_AI_moves.returnOpponentsMove(gamestate, legalMoves);
			if(legalMoves.size() != 0){
				//make AI move
				makeMove(gamestate, opponentMove);
				//update legal moves
				getLegalMoves(legalMoves, theoreticalMoves, gamestate);
			} else {
				//TODO: implement handling no legal moves (to nothing?)
			}
		}

		//update screen
		screen.update(gamestate, legalMoves, xC, yC, EndMove);

		// waiting timer: necessary for syncing 
		SDL_Delay(floor(2.0f));
		
	} 
    screen.close();

    return 0;
}