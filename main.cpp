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

//TODO: remove using namespace std everywhere

int main(int argc, char *argv[])
{
	//FIXME: king moves
	//TODO: implement this file as an app with object orientated programming
	//TODO: implement sound effects
	Screen screen;
	if(screen.init()==false){
		cout<<"Error initialising SDL."<<endl;
		return 1;
	}

    GameState gamestate;
    MoveCoord moveCoord;
    SDL_Event event;
	//handles AI moves
	AI_Handler handler_AI_moves;
	std::vector<Move> legalMoves;
	std::vector<Move> theoreticalMoves;
	int mx;
	int my;
	int xC;
	int yC;
	bool humanTurn;

	bool gameover = false;
    bool WhiteHuman = true;
    bool BlackHuman = false;
	int square = screen.SCREEN_WIDTH/8;
	bool StartMove =true;
	bool EndMove = false;
	bool running = true;
	
	//get legal moves for gamestate
	getLegalMoves(legalMoves, theoreticalMoves, gamestate);

    // Draw init board
    screen.update(gamestate, legalMoves, xC, yC, false);

	bool QUIT = false;
	while (!QUIT) {
		humanTurn = (gamestate.m_whitesTurn && WhiteHuman) || (!gamestate.m_whitesTurn && BlackHuman);
		//TODO: does PollEvent work like intended? 
		//maybe runs code whenever an event occurs 
		//RUNS when every event is happening like moving the mouse
		if(SDL_WaitEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					QUIT=true;
					break;
				//move pieces via mouse clicks
				case SDL_MOUSEBUTTONDOWN:
                    //only can make moves if game is not over or players turn
                    if (!gameover && humanTurn){
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
					break;  
				case SDL_KEYDOWN:
					//undo Move
					if (event.key.keysym.sym == SDLK_z) {
						LOG("[LOG]: Undoing a move.");
						undoMove(gamestate);
					}
					//reset game
					else if (event.key.keysym.sym == SDLK_r) {
						LOG("[LOG]: Resetting the game.");
						//delete gamestate
						gamestate.~GameState(); 
						//place new gamestate object in memory of old object
						new (&gamestate) GameState(); 
						getLegalMoves(legalMoves, theoreticalMoves, gamestate);
						StartMove = true;
						EndMove = false;
						moveCoord = MoveCoord();
						gameover = false;
					}
					break; 
			}
		}

		//AI Moves
		if(!gameover && !humanTurn){
			Move opponentMove;
			// get best AI move from legal moves
			opponentMove = handler_AI_moves.returnOpponentsMove1StepLook(gamestate, legalMoves);
			if(legalMoves.size() != 0){
				//make AI move
				makeMove(gamestate, opponentMove);
				//update legal moves
				getLegalMoves(legalMoves, theoreticalMoves, gamestate);
				// LOG(handler_AI_moves.returnScore(gamestate));
			} else {
				//TODO: implement handling no legal moves (to nothing?)
			}
		}

        if(gamestate.m_checkmate){
            gameover = true;
            if(gamestate.m_whitesTurn){
				//TODO: move this in screen update
				//TODO: draw on the screen and remove quit
				cout<<"Black wins by Checkmate."<<endl;
				QUIT=true;
			}
            else{
				//TODO: draw on the screen and remove quit
				cout<<"White wins by Checkmate."<<endl;
				QUIT=true;
			}

		} else if (gamestate.m_stalemate){
			gameover = true;
			//TODO: draw on the screen and remove quit
			cout<<"Stalemate."<<endl;
			QUIT=true;
		}
		
		//update screen
		screen.update(gamestate, legalMoves, xC, yC, EndMove);

		// waiting timer: necessary for syncing 
		SDL_Delay(floor(2.0f));
		
	} 
    screen.close();

    return 0;
}