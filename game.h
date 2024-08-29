#ifndef GAME_H
#define GAME_H

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


class Game {
public:
    //constructor of game
    Game();
    //destructor of game
    ~Game();
    //run the game
    void run();

private:
    //handles events of player (interation with user)
    void handleEvents();
    //resets the game
    void resetGame();
    //handles the moves of the player
    void processPlayerMove();
    //handles the moves of the AI
    void processAIMove();
    //check if game is over
    void checkGameOver();

    bool gameover;
    bool WhiteHuman;
    bool BlackHuman;
    int square;
    bool StartMove;
    bool EndMove;
    bool running;
    bool humanTurn;
    int xC;
	int yC;
    Screen screen;
    GameState gamestate;
    MoveCoord moveCoord;
    AI_Handler handler_AI_moves;
    std::vector<Move> legalMoves;
    std::vector<Move> theoreticalMoves;

};

#endif // GAME_H



