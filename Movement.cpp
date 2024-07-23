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
                if(gamestate.m_chessBoard[y][x] == 11)
                    getPawnMoves(legalMoves, gamestate, x, y);
                }
        }    
    } 
}



void getPawnMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y){
    //TODO: optimize this function
    //direction, homeSquare, moveCoord can be init in advance

    //direction changes depending on the color
    int direction;
    int homeSquare;
    if(gamestate.m_whitesTurn){
        direction = -1;
        homeSquare = 6;
    } else {
        direction = 1;
        homeSquare = 1;
    }

    //This can be init in the getlegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
	moveCoord.yStart = y;

    //check if piece still can move to the front square and if it is empty 
    if(!(y== 7 || y==0) && gamestate.m_chessBoard[y+direction][x]==0){
        moveCoord.xEnd = x;
        moveCoord.yEnd = y + direction;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

    //front 2x square is empty and starting pawn pose
    if(y == homeSquare && gamestate.m_chessBoard[y+direction*2][x]==0 ){
        moveCoord.xEnd = x;
        moveCoord.yEnd = y + direction*2;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

    //check if there is an attack square and if there is an enemey piece on it (right)
    if(!(y== 7 || y==0) && x!=7 && gamestate.m_chessBoard[x+1][y+direction] != 0 && !gamestate.isPieceTurn(x+1,y+direction)){
        moveCoord.xEnd = x + 1;
        moveCoord.yEnd = y + direction;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

    //check if there is an attack square and if there is an enemey piece on it (left)
    if(!(y== 7 || y==0) && x!=0 && gamestate.m_chessBoard[x-1][y+direction] != 0 && !gamestate.isPieceTurn(x-1,y+direction)){
        moveCoord.xEnd = x - 1;
        moveCoord.yEnd = y + direction;
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

