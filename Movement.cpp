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
                else if(gamestate.m_chessBoard[y][x] == 22)
                    getRookMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 23)
                    getKnightMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 24)
                    getBishopMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 26)
                    getKingMoves(legalMoves, gamestate, x, y);
                }
            //blacks turn and piece is black
            else if(gamestate.m_chessBoard[y][x] > 0 && gamestate.m_chessBoard[y][x] < 20 && !gamestate.m_whitesTurn){
                if(gamestate.m_chessBoard[y][x] == 11)
                    getPawnMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 12)
                    getRookMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 13)
                    getKnightMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 14)
                    getBishopMoves(legalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 16)
                    getKingMoves(legalMoves, gamestate, x, y);
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
    if(y == homeSquare && gamestate.m_chessBoard[y+direction*2][x]==0 && gamestate.m_chessBoard[y+direction][x]==0){
        moveCoord.xEnd = x;
        moveCoord.yEnd = y + direction*2;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

    //check if there is an attack square and if there is an enemey piece on it (right)
    if(!(y== 7 || y==0 || x==7) && gamestate.m_chessBoard[y+direction][x+1] != 0 && !gamestate.isPieceTurn(x+1,y+direction)){
        moveCoord.xEnd = x + 1;
        moveCoord.yEnd = y + direction;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }

    //check if there is an attack square and if there is an enemey piece on it (left)
    if(!(y== 7 || y==0 || x==0) && gamestate.m_chessBoard[y+direction][x-1] != 0 && !gamestate.isPieceTurn(x-1,y+direction)){
        moveCoord.xEnd = x - 1;
        moveCoord.yEnd = y + direction;
        Move move(gamestate.m_chessBoard, moveCoord);
        legalMoves.push_back(move);
    }
}



void getKnightMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y) {
    //TODO: optimize this function
    // Array to hold the possible knight moves
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    // This can be initialized in the getLegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
    moveCoord.yStart = y;

    // Iterate over all possible knight moves
    for (int i = 0; i < 8; ++i) {
        int newX = x + knightMoves[i][0];
        int newY = y + knightMoves[i][1];

        // Check if the new position is within the bounds of the board
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Check if the new position is either empty or contains an enemy piece
            if (gamestate.m_chessBoard[newY][newX] == 0 || !gamestate.isPieceTurn(newX, newY)) {
                moveCoord.xEnd = newX;
                moveCoord.yEnd = newY;
                Move move(gamestate.m_chessBoard, moveCoord);
                legalMoves.push_back(move);
            }
        }
    }
}



void getRookMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y) {
    // This can be initialized in the getLegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
    moveCoord.yStart = y;

    // Directions the rook can move in (right, left, down, up)
    int directions[4][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    // Iterate over all possible directions
    for (int i = 0; i < 4; ++i) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int newX = x + dx;
        int newY = y + dy;

        // Continue moving in the current direction until the end of the board or a piece is encountered
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Check if the new position is empty
            if (gamestate.m_chessBoard[newY][newX] == 0) {
                moveCoord.xEnd = newX;
                moveCoord.yEnd = newY;
                Move move(gamestate.m_chessBoard, moveCoord);
                legalMoves.push_back(move);
            } else {
                // If the position is occupied by an enemy piece, add the move and stop in this direction
                if (!gamestate.isPieceTurn(newX, newY)) {
                    moveCoord.xEnd = newX;
                    moveCoord.yEnd = newY;
                    Move move(gamestate.m_chessBoard, moveCoord);
                    legalMoves.push_back(move);
                }
                // Stop in this direction regardless of whether the piece is friendly or enemy
                break;
            }
            // Move further in the current direction
            newX += dx;
            newY += dy;
        }
    }
}


void getBishopMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y) {
    // This can be initialized in the getLegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
    moveCoord.yStart = y;

    // Directions the bishop can move in (top-right, top-left, bottom-right, bottom-left)
    int directions[4][2] = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    // Iterate over all possible directions
    for (int i = 0; i < 4; ++i) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int newX = x + dx;
        int newY = y + dy;

        // Continue moving in the current direction until the end of the board or a piece is encountered
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Check if the new position is empty
            if (gamestate.m_chessBoard[newY][newX] == 0) {
                moveCoord.xEnd = newX;
                moveCoord.yEnd = newY;
                Move move(gamestate.m_chessBoard, moveCoord);
                legalMoves.push_back(move);
            } else {
                // If the position is occupied by an enemy piece, add the move and stop in this direction
                if (!gamestate.isPieceTurn(newX, newY)) {
                    moveCoord.xEnd = newX;
                    moveCoord.yEnd = newY;
                    Move move(gamestate.m_chessBoard, moveCoord);
                    legalMoves.push_back(move);
                }
                // Stop in this direction regardless of whether the piece is friendly or enemy
                break;
            }
            // Move further in the current direction
            newX += dx;
            newY += dy;
        }
    }
}


void getKingMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y) {
    // This can be initialized in the getLegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
    moveCoord.yStart = y;

    // Directions the king can move in (8 possible moves)
    int directions[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // Horizontal and vertical
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Diagonal
    };

    // Iterate over all possible directions
    for (int i = 0; i < 8; ++i) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check if the new position is within the board
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Check if the new position is either empty or occupied by an enemy piece
            if (gamestate.m_chessBoard[newY][newX] == 0 || !gamestate.isPieceTurn(newX, newY)) {
                moveCoord.xEnd = newX;
                moveCoord.yEnd = newY;
                Move move(gamestate.m_chessBoard, moveCoord);
                legalMoves.push_back(move);
            }
        }
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

