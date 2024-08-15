#include "opponent.h"


Move AI_Handler::returnOpponentsMove(const GameState &gamestate, const std::vector<Move> &legalMoves){
    float score;
    score = returnScore(gamestate);
    LOG(score);
    return legalMoves[0];
}

AI_Handler::AI_Handler() {
}


float AI_Handler::returnScore(const GameState &gamestate) {
    float whiteScore = 0;
    float blackScore = 0;
    int piece;
    int pieceScore;
    int positionScore;

    //evaluate the board
   for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            piece = gamestate.m_chessBoard[y][x];
            //piece detected
            if(piece!=EMPTY){
                pieceScore = PieceScoreMap[piece];
                
                //get score of position
                if (piece == whitePawn) {
                    positionScore = whitePawnMap[y][x];
                } else if (piece == blackPawn) {
                    positionScore = blackPawnMap[y][x];
                } else if (piece == whiteRook) {
                    positionScore = whiteRookMap[y][x];
                } else if (piece == blackRook) {
                    positionScore = blackRookMap[y][x];
                } else if (piece == whiteKnight) {
                    positionScore = whiteKnightMap[y][x];
                } else if (piece == blackKnight) {
                    positionScore = blackKnightMap[y][x];
                } else if (piece == whiteBishop) {
                    positionScore = whiteBishopMap[y][x];
                } else if (piece == blackBishop) {
                    positionScore = blackBishopMap[y][x];
                } else if (piece == whiteQueen) {
                    positionScore = whiteQueenMap[y][x];
                } else if (piece == blackQueen) {
                    positionScore = blackQueenMap[y][x];
                } else if (piece == whiteKing) {
                    positionScore = whiteKingMap[y][x];
                } else if (piece == blackKing) {
                    positionScore = blackKingMap[y][x];
                }

                //white pieces have a positive score
                if (pieceScore>0){
                    whiteScore += pieceScore + positionScore*position_weight;
                }
                //black pieces have a negative score
                else{
                    //negative since positionScore is positive
                    blackScore += pieceScore - positionScore*position_weight;
                }
            }
        }
    }
    return whiteScore + blackScore;
}
