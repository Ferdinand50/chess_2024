#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
<<<<<<< HEAD
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
							screen.update(gamestate.m_chessBoard);

							//get legal moves
							getLegalMoves(legalMoves, gamestate);
						}
					}
			}
		}
		SDL_Delay(floor(32.0f));
	} 
    screen.close();

    return 0;
}
=======
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
>>>>>>> 6083e5b (Initial commit)
