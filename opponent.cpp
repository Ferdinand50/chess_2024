#include "opponent.h"

AI_Handler::AI_Handler(): searchDepth(4), position_weight(0.1), checkmateScore(1000), stalemateScore(0) {
}


Move AI_Handler::returnBestMove(GameState gamestate, const std::vector<Move> legalMoves){
    float score = returnBestMoveMinMax(gamestate, legalMoves, searchDepth);
    return bestMoveAI;
}


float AI_Handler::returnBestMoveMinMax(GameState &gamestate, const std::vector<Move> &legalMoves, int depth) {
    //int turnMultiplier = gamestate.m_whitesTurn ? 1 : -1;
    int turnMultiplier = 1;
    float currentScore;
    float score;
    float maxScore;
    float minScore;

    //evaluate board
    if(depth == 0){
        //positive if white negative if black
        if(gamestate.m_checkmate){
            currentScore = checkmateScore * turnMultiplier;
        }
        //if stalemate is possible score will set to neutral, there move will be only made if own score is worse than 0
        else if(gamestate.m_stalemate){
            currentScore = stalemateScore;
        }
        //score the current moves made
        else {
            currentScore = turnMultiplier * returnScore(gamestate);
        }
        return currentScore;
    }
    //whites layer
    if(gamestate.m_whitesTurn){
        maxScore = -checkmateScore;
        //TODO: remove theoreticalMoves
        std::vector<Move> localLegalMoves;
        std::vector<Move> localTheoreticalMoves;
        getLegalMoves(localLegalMoves, localTheoreticalMoves, gamestate);
        for (const Move &localMove : localLegalMoves) {
            makeMove(gamestate, localMove);
            score = returnBestMoveMinMax(gamestate, localLegalMoves, depth-1);
            if(score>maxScore){
                maxScore = score;
                //end search
                if(depth == searchDepth){
                    bestMoveAI = localMove;
                }
            }
            undoMove(gamestate);
        }
        return maxScore;
    }
    //black layer
   if(!gamestate.m_whitesTurn){
        minScore = checkmateScore;
        //TODO: remove theoreticalMoves
        std::vector<Move> localLegalMoves;
        std::vector<Move> localTheoreticalMoves;
        getLegalMoves(localLegalMoves, localTheoreticalMoves, gamestate);
        for (const Move &localMove : localLegalMoves) {
            makeMove(gamestate, localMove);
            score = returnBestMoveMinMax(gamestate, localLegalMoves, depth-1);
            if(score<minScore){
                minScore = score;
                //end search
                if(depth == searchDepth){
                    bestMoveAI = localMove;
                }
            }
            undoMove(gamestate);
        }
        return minScore;
    }
    LOG("[LOG]: Error in returnBestMoveMinMax function.");
    return 0.0f;
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
                    //whiteScore += pieceScore;
                }
                //black pieces have a negative score
                else{
                    //negative since positionScore is positive
                    blackScore += pieceScore - positionScore*position_weight;
                    //blackScore += pieceScore;
                }
            }
        }
    }
    return whiteScore + blackScore;
}
