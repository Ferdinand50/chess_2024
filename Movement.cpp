#include "Movement.h"



void makeMove(int (&chessBoard)[8][8], Move move){
    //remove piece of start square
    chessBoard[move.m_start_y][move.m_start_x] = 0;

    // //move piece to new square
    chessBoard[move.m_end_y][move.m_end_x] = move.m_pieceMoved;

    
}

void getLegalMoves(std::vector<Move> &legalMoves, const GameState &gamestate){
    // Clear the elements of legalMoves vector
    legalMoves.clear();

    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            //whites turn and piece is white
            if(gamestate.m_chessBoard[y][x]>20 && gamestate.m_whitesTurn){
                if(gamestate.m_chessBoard[y][x] == 21)
                    getPawnMoves(legalMoves, gamestate, x, y);
                }
            //blacks turn and piece is black
            else if(gamestate.m_chessBoard[y][x] > 0 && gamestate.m_chessBoard[y][x] < 20 && !gamestate.m_whitesTurn){
                }
        }    
    } 
}


void getPawnMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y){
    //TODO: white and black pawn
    // use offsett variable
    // only till 0 (inside the board)

    //TODO: this will fail if x or y is out of the board

    //This can be init in the getlegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
	moveCoord.yStart = y;

    //front square is empty 
    if(gamestate.m_chessBoard[y-1][x]==0){
        moveCoord.xEnd = x;
        moveCoord.yEnd = y - 1;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

    //front 2x square is empty and starting pawn pose
    if(y == 6 && gamestate.m_chessBoard[y-2][x]==0 ){
        moveCoord.xEnd = x;
        moveCoord.yEnd = y - 2;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

}


// Move class 
//TODO: USE reference here
Move::Move(int const chessBoard[8][8], MoveCoord moveCoord){
    m_pieceMoved = chessBoard[moveCoord.yStart][moveCoord.xStart];
    m_pieceTaken = chessBoard[moveCoord.yEnd][moveCoord.xEnd];

    m_start_x = moveCoord.xStart;
    m_start_y = moveCoord.yStart;
    m_end_x = moveCoord.xEnd;
    m_end_y = moveCoord.yEnd;
}


bool Move::isLegal(std::vector<Move> const &legalMoves){
    for (const Move& legalMove : legalMoves) {
        if(m_start_x == legalMove.m_start_x &&
               m_start_y == legalMove.m_start_y &&
               m_end_x == legalMove.m_end_x &&
               m_end_y == legalMove.m_end_y &&
               m_pieceMoved == legalMove.m_pieceMoved &&
               m_pieceTaken == legalMove.m_pieceTaken){
                return true;
               }
    }
    return false;
}



void Move::close(){

}

