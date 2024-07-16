#include "Movement.h"



void makeMove(int (&chessBoard)[8][8], Move move){
    //remove piece of start square
    chessBoard[move.m_start_x][move.m_start_y] = 0;

    // //move piece to new square
    chessBoard[move.m_end_x][move.m_end_y] = move.m_pieceMoved;

    //TODO: update list of pieces
}

void getLegalMoves(std::vector<Move> &legalMoves, int (&chessBoard)[8][8]){
    // Clear the elements of legalMoves vector
    legalMoves.clear();
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

