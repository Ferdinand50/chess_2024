#include "opponent.h"

AI_Handler::AI_Handler(): searchDepth(4), position_weight(0.1), checkmateScore(1000), stalemateScore(0) {
}


Move AI_Handler::returnBestMove(GameState gamestate, const std::vector<Move> legalMoves){
    int turnMultiplier = gamestate.m_whitesTurn ? 1 : -1;
    float score = findMoveNegaMaxAlphaBeta(gamestate, legalMoves, searchDepth, -2000, 2000, turnMultiplier);
    return bestMoveAI;
}


float AI_Handler::findMoveNegaMaxAlphaBeta(GameState &gamestate, const std::vector<Move> &legalMoves, int depth, float alpha, float beta, int turnMultiplier) {
    float currentScore;
    float maxScore = -checkmateScore;  // -CHECKMATE in Python
    float score;

    // Base case: if the depth is zero, evaluate the position
    if (depth == 0) {
        if (gamestate.m_checkmate) {
            currentScore = checkmateScore * turnMultiplier;
        //FIXME: if enabled AI makes stalemates moves in good positions for itself
        // } else if (gamestate.m_stalemate) {
        //     currentScore = stalemateScore;
        } else {
            currentScore = turnMultiplier * returnScore(gamestate);
        }
        return currentScore;
    }

    // Iterate over all legal moves
    for (const Move &move : legalMoves) {
        // Make the move
        makeMove(gamestate, move);

        // Get legal moves after the move
        std::vector<Move> localLegalMoves;
        std::vector<Move> localTheoreticalMoves;
        getLegalMoves(localLegalMoves, localTheoreticalMoves, gamestate);

        // Recursive call with negamax
        score = -findMoveNegaMaxAlphaBeta(gamestate, localLegalMoves, depth - 1, -beta, -alpha, -turnMultiplier);

        // Undo the move
        undoMove(gamestate);

        // Update maxScore
        if (score > maxScore) {
            maxScore = score;
            if (depth == searchDepth) {  // Replace DEPTH with searchDepth or the appropriate depth variable
                bestMoveAI = move;
            }
        }

        // Alpha-beta pruning
        if (maxScore > alpha) {
            alpha = maxScore;
        }
        if (alpha >= beta) {
            break;  // Cutoff
        }
    }

    return maxScore;
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
