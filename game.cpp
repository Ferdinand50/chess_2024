#include "game.h"

Game::Game(): gameover(false), WhiteHuman(true), BlackHuman(false), square(screen.SCREEN_WIDTH/8), 
                StartMove(true), EndMove(false), running(true){
    //init SDL screen
    screen.init();
    //get legal moves for gamestate
    getLegalMoves(legalMoves, theoreticalMoves, gamestate);
    // Draw init board
    screen.update(gamestate, legalMoves, xC, yC, false);
}


Game::~Game() {
    screen.close();
}


void Game::run() {
    while(running) {
        //handle events from the player(human)
        handleEvents();
        if (!gameover) {
            //if CPU turns get AI move
            if (!humanTurn) 
                processAIMove();
            //check if the game is over
            checkGameOver();
            //update screen
            if(!gameover)
                screen.update(gamestate, legalMoves, xC, yC, EndMove);
        }
        //waiting
        SDL_Delay(floor(2.0f));
    }
}


void Game::handleEvents() {
    SDL_Event event;
    humanTurn = (gamestate.m_whitesTurn && WhiteHuman) || (!gamestate.m_whitesTurn && BlackHuman);
    //RUNS when every event is happening like moving the mouse
    if(SDL_WaitEvent(&event)) {
        switch (event.type) {
            //close the game
            case SDL_QUIT:
                running = false;
                break;
            //move pieces via mouse clicks
            case SDL_MOUSEBUTTONDOWN:
                xC = event.button.x / square;
                yC = event.button.y / square;
                processPlayerMove();
                break;
            case SDL_KEYDOWN:
                //undo Move
                if (event.key.keysym.sym == SDLK_z) {
                    LOG("[LOG]: Undoing a move.");
                    undoMove(gamestate);
                    //if there is an AI player then two moves need to be undone 
                    if(!(BlackHuman&&WhiteHuman))
                        undoMove(gamestate);
                //reset game
                } else if (event.key.keysym.sym == SDLK_r) {
                    LOG("[LOG]: Resetting the game.");
                    resetGame();
                }
                break;
        }
    }
}


void Game::resetGame(){
    //delete gamestate
    gamestate.~GameState(); 
    //place new gamestate object in memory of old object
    new (&gamestate) GameState(); 
    StartMove = true;
    EndMove = false;
    moveCoord = MoveCoord();
    gameover = false;
}


void Game::processPlayerMove(){
    //only can make moves if game is not over or players turn
    if (!gameover && humanTurn){
        int mx;
	    int my;
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
                    //make sound effect
                    screen.playMoveSoundEffect(move);
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
}


void Game::processAIMove(){
    //AI Moves
    Move opponentMove;
    // get best AI move from legal moves
    opponentMove = handler_AI_moves.returnBestMove(gamestate, legalMoves);
    if(legalMoves.size() != 0){
        //make AI move
        makeMove(gamestate, opponentMove);
        //make sound effect
        screen.playMoveSoundEffect(opponentMove);
    } else {
        LOG("AI has no legal move");
    }
}


void Game::checkGameOver(){
    //get legal moves for this gamestate
    getLegalMoves(legalMoves, theoreticalMoves, gamestate);
    if(gamestate.m_checkmate){
        gameover = true;
        screen.update(gamestate, legalMoves, xC, yC, EndMove);
        if(gamestate.m_whitesTurn){
            screen.renderText("Black wins by Checkmate.");
        }
        else{
            screen.renderText("White wins by Checkmate.");
        }

    } else if (gamestate.m_stalemate){
        gameover = true;
        screen.update(gamestate, legalMoves, xC, yC, EndMove);
        screen.renderText("Stalemate");
    }
}







