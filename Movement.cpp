#include "Movement.h"


//TODO: use reference
void makeMove(int (*chessBoard)[8][8], Move move)
{
    // //move piece to new square


    //remove piece of start square
    *chessBoard[move.m_start_x][move.m_start_y] = 0;


}






// Move class 
Move::Move(int const chessBoard[8][8], MoveCoord moveCoord)
{
    m_pieceMoved = chessBoard[moveCoord.xStart][moveCoord.yStart];
    m_pieceTaken = chessBoard[moveCoord.xEnd][moveCoord.yEnd];

    m_start_x = moveCoord.xStart;
    m_start_y = moveCoord.yStart;
    m_end_x = moveCoord.xEnd;
    m_end_y = moveCoord.yEnd;
}





void Move::close()
{

}

