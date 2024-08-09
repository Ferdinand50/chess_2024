#include "Movement.h"


void makeMove(GameState &gamestate, Move move){
    //remove piece of start square
    gamestate.m_chessBoard[move.m_start_y][move.m_start_x] = 0;
    //move piece to new square
    gamestate.m_chessBoard[move.m_end_y][move.m_end_x] = move.m_pieceMoved;
    //change turn of player
    gamestate.m_whitesTurn = !gamestate.m_whitesTurn;
    //log selected move
    gamestate.moveLog.push(move);

    //update King position
    //white King
    if(move.m_pieceMoved==26)
        gamestate.m_whiteKingPosition = {move.m_end_y, move.m_end_x};
    //black King
    else if(move.m_pieceMoved==16)
        gamestate.m_blackKingPosition = {move.m_end_y, move.m_end_x};
}

void undoMove(GameState &gamestate){
    //check if log is not empty
    if (!gamestate.moveLog.empty()) {
        Move move = gamestate.moveLog.top();
        gamestate.moveLog.pop();

        gamestate.m_chessBoard[move.m_start_y][move.m_start_x] = move.m_pieceMoved;
        gamestate.m_chessBoard[move.m_end_y][move.m_end_x] = move.m_pieceTaken;
        //change turn of player
        gamestate.m_whitesTurn = !gamestate.m_whitesTurn;

        // Update King position
        // White King
        if(move.m_pieceMoved == 26) {
            gamestate.m_whiteKingPosition = {move.m_start_y, move.m_start_x};
        }
        // Black King
        else if(move.m_pieceMoved == 16) {
            gamestate.m_blackKingPosition = {move.m_start_y, move.m_start_x};
        }

    } else {
        std::cout<<"No move to undo"<<std::endl;
    }
}

void getLegalMoves(std::vector<Move> &legalMoves, std::vector<Move> &theoreticalMoves, const GameState &gamestate){
    // Clear the elements of legalMoves vector
    legalMoves.clear();
    //TODO: implement caslt rights
    //tempCastleRights = backend.CastleRights(gs.currentCastleRights.bqs, gs.currentCastleRights.bks, gs.currentCastleRights.wqs, gs.currentCastleRights.wks)
    //update check and pins
    checkForPinsAndChecks(gamestate);

    int king_x;
    int king_y;

    if (gamestate.m_whitesTurn) {
        king_y = gamestate.m_whiteKingPosition[0];
        king_x = gamestate.m_whiteKingPosition[1];
    } else {
        king_y = gamestate.m_blackKingPosition[0];
        king_x = gamestate.m_blackKingPosition[1];
    }

    //King in Check
    if(gamestate.m_inCheck){
        //one check
        if(gamestate.m_checks.size() == 1){
            getTheoreticalMoves(theoreticalMoves, gamestate);
            //block check
            std::vector<int> check = gamestate.m_checks[0];
            int check_x = check[0];
            int check_y = check[1];
            //enemy piece causing the check
            int pieceCheckingType = getPieceType(gamestate, check_x, check_y);
            //squares that pieces can move to
            std::set<std::pair<int, int>> validSquares;
            //if knight capture it or move king (check can not be blocked)
            if(pieceCheckingType == 3){
                validSquares.insert({check_x, check_y});
            //check can be blocked
            } else {
                for (int i = 1; i <= 7; ++i) {
                    //check[2] and check[3] are the check directions
                    int validSquare_x = king_x + check[2] * i;
                    int validSquare_y = king_y + check[3] * i;
                    validSquares.insert({validSquare_x, validSquare_y});
                    //once you get to piece end checks
                    if(validSquare_x == check_x && validSquare_y == check_y)
                        break;
                }
            }
            //deletes moves which are not legal
            //backwards iteration
            for (int i = static_cast<int>(theoreticalMoves.size()) - 1; i >= 0; --i){
                //move doesnt move king so it must block or capture
                //TODO: check if rank and file is correct x and y
                if (theoreticalMoves[i].m_pieceMoved != 16 && theoreticalMoves[i].m_pieceMoved != 26) {
                    //move doesnt block or capture
                    if (validSquares.find({theoreticalMoves[i].m_end_x, theoreticalMoves[i].m_end_y}) == validSquares.end()) {
                        theoreticalMoves.erase(theoreticalMoves.begin() + i);
                    }
                }
            }
            //TODO: implement caslt rights
            //gs.currentCastleRights = tempCastleRights
        }
        //double check king has to move
        else
            //TODO: fix king moves
            getKingMoves(theoreticalMoves, gamestate, king_x, king_y);
    }

    //all moves are fine
    else {
        getTheoreticalMoves(theoreticalMoves, gamestate);
        //get castle moves only possible if there is no check
        //TODO: implement castle moves
        //gs.currentCastleRights = tempCastleRights
        //moves = getCastleMoves(gs, position_rank, position_file, moves)
    }
    //TODO: only use legal moves vector
    legalMoves = theoreticalMoves;
    CheckmateandStalemate(legalMoves, gamestate);
}


void getTheoreticalMoves(std::vector<Move> &theoreticalMoves, const GameState &gamestate){
    // Clear the elements of legalMoves vector
    theoreticalMoves.clear();

    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            //whites turn and piece is white
            if(gamestate.m_chessBoard[y][x]>20 && gamestate.m_whitesTurn){
                if(gamestate.m_chessBoard[y][x] == 21)
                    getPawnMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 22)
                    getRookMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 23)
                    getKnightMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 24)
                    getBishopMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 25)
                    getQueenMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 26)
                    getKingMoves(theoreticalMoves, gamestate, x, y);
                }
            //blacks turn and piece is black
            else if(gamestate.m_chessBoard[y][x] > 0 && gamestate.m_chessBoard[y][x] < 20 && !gamestate.m_whitesTurn){
                if(gamestate.m_chessBoard[y][x] == 11)
                    getPawnMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 12)
                    getRookMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 13)
                    getKnightMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 14)
                    getBishopMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 15)
                    getQueenMoves(theoreticalMoves, gamestate, x, y);
                else if(gamestate.m_chessBoard[y][x] == 16)
                    getKingMoves(theoreticalMoves, gamestate, x, y);
                }
        }    
    } 
}


void CheckmateandStalemate(const std::vector<Move> &legalMoves, const GameState &gamestate){
    //no Moves left so it is game over
    if(legalMoves.size()==0){
        if(gamestate.m_inCheck)
            gamestate.m_checkmate = true;
    }
        else if (!gamestate.m_inCheck)
            gamestate.m_stalemate = true;
}


//TODO: this function modifies the gamestate is this okay? (checks, pins, inCheck)
void checkForPinsAndChecks(const GameState &gamestate){
    //clear the pins and checks vector
    gamestate.m_pins.clear();
    gamestate.m_checks.clear();
    //set inCheck to False
    gamestate.m_inCheck = false;

    int king_x;
    int king_y;

    if (gamestate.m_whitesTurn) {
        king_y = gamestate.m_whiteKingPosition[0];
        king_x = gamestate.m_whiteKingPosition[1];
    } else {
        king_y = gamestate.m_blackKingPosition[0];
        king_x = gamestate.m_blackKingPosition[1];
    }

    //checking from King location outward for pins and ckechs, pins get stored
    int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    // Iterate over all possible directions
    for (int i = 0; i < 8; ++i) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int newX = king_x + dx;
        int newY = king_y + dy;
        //counter to check how many step have been gone so far
        int step_gone = 1;

        std::vector<int> PossiblePin;

        // Continue moving in the current direction until the end of the board or a piece is encountered
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Check if the new position has a piece
            if (gamestate.m_chessBoard[newY][newX] != 0) {
                // If the position is occupied by an alley piece
                if (gamestate.isPieceTurn(newX, newY)) {
                    //only first ally piece can be pinned
                    if (PossiblePin.empty())
                        PossiblePin = {newX, newY, directions[i][0], directions[i][1]};
                    //already second pin so no need to check for further pins
                    else
                        break;
                
                }
                // If the position is occupied by an enemy piece
                if (!gamestate.isPieceTurn(newX, newY)) {
                    //declaration of type of selected piece
                    //vertical + horizontal multiple squares: Queen and Rook
                    //vertical + horizontal single squares: Queen, King Rook
                    //diagonal multiple squares: Queen, Bishop 
                    //diagonal single squares: Queen, King, Bishop and Pawn
                    //pawn: 1 Rook: 2 Knight: 3 Bishop: 4 Queen: 5 King: 6
                    int type = getPieceType(gamestate, newX, newY);
                    //TODO: check if gamestate white turn is correct
                    if ((0 <= i && i <= 3 && type == 2) || (4 <= i && i <= 7 && type == 4) || (step_gone == 1 && type == 1 && ((!gamestate.m_whitesTurn && 6 <= i && i <= 7) || (gamestate.m_whitesTurn && 4 <= i && i <= 5))) || (type == 5) || (step_gone == 1 && type == 6)) {
                        //no pin so its check
                        if (PossiblePin.empty()){
                            gamestate.m_inCheck = true;
                            gamestate.m_checks.push_back({newX, newY, directions[i][0], directions[i][1]});
                            break;
                        }
                        //allied piece is blocking check so pin
                        else
                            gamestate.m_pins.push_back(PossiblePin);
                    }
                    //enemy piece but not applying check
                    else
                        break;
                }
            }
            // Move further in the current direction
            newX += dx;
            newY += dy;
            step_gone += 1;
        }
    }
    //check for knights checks
    int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int j = 0; j < 8; ++j) {
        int newX = king_x + knightMoves[j][0];
        int newY = king_y + knightMoves[j][1];
        //check board boundaries
        if(newX >= 0 && newX < 8 && newY >= 0 && newY < 8){
            int type = getPieceType(gamestate, newX, newY);
            //enemy knight
            if(type==3 && !gamestate.isPieceTurn(newX, newY)){
                gamestate.m_inCheck = true;
                gamestate.m_checks.push_back({newX, newY, knightMoves[j][0], knightMoves[j][1]});
            }
        }
    }
}

int getPieceType(const GameState &gamestate, int x, int y){
    int piece = gamestate.m_chessBoard[y][x];
    std::string pieceStr = std::to_string(piece);
    return pieceStr[1] - '0'; // Convert the character to an integer
}


void getPawnMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y){
    //check is piece is pinned
    bool piecePinned = false;
    std::vector<int> pinDirection = {0, 0};

    //vertical directions
    std::vector<int> v1 = {0, -1};
    std::vector<int> v2 = {0, 1};
    //diagonal right
    std::vector<int> dr1 = {1, -1};
    std::vector<int> dr2 = {1, 1};
    //diagonal left
    std::vector<int> dl1 = {-1, -1};
    std::vector<int> dl2 = {-1, 1};

    //check if piece is pinned
    for (int i = gamestate.m_pins.size() - 1; i >= 0; --i) {
        if (gamestate.m_pins[i][0] == x && gamestate.m_pins[i][1] == y) {
            piecePinned = true;
            pinDirection = {gamestate.m_pins[i][2], gamestate.m_pins[i][3]};
            break;
        }
    }

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
        //check if piece is pinned or can move in pin direction
        if(!piecePinned || (pinDirection == v1 || pinDirection == v2)){
            moveCoord.xEnd = x;
            moveCoord.yEnd = y + direction;
            Move move(gamestate, moveCoord);
            legalMoves.push_back(move);
        }
    }

    //front 2x square is empty and starting pawn pose
    if(y == homeSquare && gamestate.m_chessBoard[y+direction*2][x]==0 && gamestate.m_chessBoard[y+direction][x]==0){
        //check if piece is pinned or can move in pin direction
        if(!piecePinned || (pinDirection == v1 || pinDirection == v2)){
            moveCoord.xEnd = x;
            moveCoord.yEnd = y + direction*2;
            Move move(gamestate, moveCoord);
            legalMoves.push_back(move);
        }
    }

    //check if there is an attack square and if there is an enemy piece on it (right)
    if(!(y== 7 || y==0 || x==7) && gamestate.m_chessBoard[y+direction][x+1] != 0 && !gamestate.isPieceTurn(x+1,y+direction)){
        //check if piece is pinned or can move in pin direction
        if(!piecePinned || (pinDirection == dr1 || pinDirection == dr2)){
            moveCoord.xEnd = x + 1;
            moveCoord.yEnd = y + direction;
            Move move(gamestate, moveCoord);
            legalMoves.push_back(move);
        }
    }

    //check if there is an attack square and if there is an enemy piece on it (left)
    if(!(y== 7 || y==0 || x==0) && gamestate.m_chessBoard[y+direction][x-1] != 0 && !gamestate.isPieceTurn(x-1,y+direction)){
        //check if piece is pinned or can move in pin direction
        if(!piecePinned || (pinDirection == dr1 || pinDirection == dr2)){
            moveCoord.xEnd = x - 1;
            moveCoord.yEnd = y + direction;
            Move move(gamestate, moveCoord);
            legalMoves.push_back(move);
        }
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
                Move move(gamestate, moveCoord);
                legalMoves.push_back(move);
            }
        }
    }
}



void getRookMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y) {
    //check is piece is pinned
    bool piecePinned = false;
    std::vector<int> pinDirection = {0, 0};

    //check if piece is pinned
    for (int i = gamestate.m_pins.size() - 1; i >= 0; --i) {
        if (gamestate.m_pins[i][0] == x && gamestate.m_pins[i][1] == y) {
            piecePinned = true;
            pinDirection = {gamestate.m_pins[i][2], gamestate.m_pins[i][3]};
            break;
        }
    }

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

        // Continue moving in the current direction until the end of the board or a piece is encountered and piece is not pinned or move in pin direction
        //                     board                                piece pinned                       vertical                                                    horizontal  
        while ((newX >= 0 && newX < 8 && newY >= 0 && newY < 8) && (!piecePinned || (i<2 && pinDirection[0] == 0 && abs(pinDirection[1]) == 1) || (i>1 && abs(pinDirection[0]) == 1 && pinDirection[1] == 0))) {
            // Check if the new position is empty
            if (gamestate.m_chessBoard[newY][newX] == 0) {
                moveCoord.xEnd = newX;
                moveCoord.yEnd = newY;
                Move move(gamestate, moveCoord);
                legalMoves.push_back(move);
            } else {
                // If the position is occupied by an enemy piece, add the move and stop in this direction
                if (!gamestate.isPieceTurn(newX, newY)) {
                    moveCoord.xEnd = newX;
                    moveCoord.yEnd = newY;
                    Move move(gamestate, moveCoord);
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
                Move move(gamestate, moveCoord);
                legalMoves.push_back(move);
            } else {
                // If the position is occupied by an enemy piece, add the move and stop in this direction
                if (!gamestate.isPieceTurn(newX, newY)) {
                    moveCoord.xEnd = newX;
                    moveCoord.yEnd = newY;
                    Move move(gamestate, moveCoord);
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


void getQueenMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y){
    getBishopMoves(legalMoves, gamestate, x, y);
    getRookMoves(legalMoves, gamestate, x, y);
}



void getKingMoves(std::vector<Move> &legalMoves, const GameState &gamestate, int x, int y) {
    // This can be initialized in the getLegalMoves function
    MoveCoord moveCoord;
    moveCoord.xStart = x;
    moveCoord.yStart = y;

    //save inCheck, check, and pins
    bool temp_inCheck = gamestate.m_inCheck;
    std::vector<std::vector<int>> temp_checks = gamestate.m_checks;
    std::vector<std::vector<int>> temp_pins = gamestate.m_pins;

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
                //move king to this position and see if he would be in check
                if (gamestate.m_whitesTurn) {
                    gamestate.m_whiteKingPosition[0] = newY;  //y
                    gamestate.m_whiteKingPosition[1] = newX;  //x
                } else {
                    gamestate.m_blackKingPosition[0] = newY;  //y
                    gamestate.m_blackKingPosition[1] = newX;  //x
                }
                //TODO: do I need to change color of player whos turn is it?
                //check if king is in check
                checkForPinsAndChecks(gamestate);
                //not in check so move is valid
                if(!gamestate.m_inCheck){
                    moveCoord.xEnd = newX;
                    moveCoord.yEnd = newY;
                    Move move(gamestate, moveCoord);
                    legalMoves.push_back(move);
                }
            }
        }
    }
    //place king back to original position
    if (gamestate.m_whitesTurn) {
        gamestate.m_whiteKingPosition[0] = y;  //y
        gamestate.m_whiteKingPosition[1] = x;  //x
    } else {
        gamestate.m_blackKingPosition[0] = y;  //y
        gamestate.m_blackKingPosition[1] = x;  //x
    }

    //load original gamestate
    gamestate.m_inCheck = temp_inCheck;
    gamestate.m_checks = temp_checks;
    gamestate.m_pins = temp_pins;
}




// Move class 
Move::Move(const GameState &gamestate, MoveCoord moveCoord){
    m_pieceMoved = gamestate.m_chessBoard[moveCoord.yStart][moveCoord.xStart];
    m_pieceTaken = gamestate.m_chessBoard[moveCoord.yEnd][moveCoord.xEnd];

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

