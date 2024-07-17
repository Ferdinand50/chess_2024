#include "Movement.h"



void makeMove(int (&chessBoard)[8][8], Move move){
    //remove piece of start square
    chessBoard[move.m_start_x][move.m_start_y] = 0;

    // //move piece to new square
    chessBoard[move.m_end_x][move.m_end_y] = move.m_pieceMoved;

    
}

void getLegalMoves(std::vector<Move> &legalMoves, const GameState &gamestate){
    // Clear the elements of legalMoves vector
    legalMoves.clear();

    for (int row = 0; row < 8; ++row){
        for (int columm = 0; columm < 8; ++columm){
            //whites turn and piece is white
            if(gamestate.m_chessBoard[columm][row]>20 && gamestate.m_whitesTurn){
                if(gamestate.m_chessBoard[columm][row] == 21)
                    getPawnMoves(legalMoves, gamestate, columm, row);
                }
            //blacks turn and piece is black
            else if(gamestate.m_chessBoard[columm][row] > 0 && gamestate.m_chessBoard[columm][row] < 20 && !gamestate.m_whitesTurn){
                }
        }    
    } 
}


void getPawnMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int columm, int row){
    //TODO: make this function
}


// Move class 
Move::Move(int const chessBoard[8][8], MoveCoord moveCoord){
    m_pieceMoved = chessBoard[moveCoord.xStart][moveCoord.yStart];
    m_pieceTaken = chessBoard[moveCoord.xEnd][moveCoord.yEnd];

    m_start_x = moveCoord.xStart;
    m_start_y = moveCoord.yStart;
    m_end_x = moveCoord.xEnd;
    m_end_y = moveCoord.yEnd;
}





void Move::close(){

}

