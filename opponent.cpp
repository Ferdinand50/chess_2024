#include "opponent.h"

AI_Handler::AI_Handler(): searchDepth(4), position_weight(0.1), checkmateScore(1000), stalemateScore(0) {
    //amount of possible threads of the physical CPU
    int systemCores = std::thread::hardware_concurrency();
    //enough threads on the system
    if (systemCores>=12){
        numberThreads = 12;
    //CPU can not make 12 threads therefore reduce the number of threads
    } else if(systemCores>=1){
        numberThreads = systemCores - 1;
    } else {
        numberThreads = 1;
        LOG("[ERROR]: Error with amount of possible threads");
    }
    LOG("[LOG]: Number of thread used is: " << numberThreads);
}

Move AI_Handler::returnBestMove(GameState gamestate, const std::vector<Move> legalMoves){
    //TODO: check if threading works as intended
    Timer timer;

    int turnMultiplier = gamestate.m_whitesTurn ? 1 : -1;
    Move AIMove;

    //size of legalMoves is smaller then the amount of threads, therefore reduce the amount of threads accordingly
    int tempNumberThreads = numberThreads;
    if (legalMoves.size() < numberThreads){
        numberThreads = legalMoves.size();
    }

    // divide list of legalMoves
    //TODO: check if the divide is okay only ints
    size_t partSize = legalMoves.size() / numberThreads;
    std::vector<std::vector<Move>> parts;

    for (int i = 0; i < numberThreads; ++i) {
        if (i == 11) {  // last part takes all the rest
            parts.push_back(std::vector<Move>(legalMoves.begin() + i * partSize, legalMoves.end()));
        } else {
            parts.push_back(std::vector<Move>(legalMoves.begin() + i * partSize, legalMoves.begin() + (i + 1) * partSize));
        }
    }
    // copy of gamestate for each thread
    std::vector<GameState> gameStates(numberThreads, gamestate);
    // threads in vector
    std::vector<std::thread> threads;
    // start threads
    for (int i = 0; i < numberThreads; ++i) {
        threads.push_back(std::thread(
            [this, &gameStates, &parts, turnMultiplier, i]() {
                scoreForEachThread[i] = findMoveNegaMaxAlphaBeta(gameStates[i], parts[i], searchDepth, -2000, 2000, turnMultiplier, i);
            }
        ));
    }
    // waiting to finish all threads
    for (int i = 0; i < numberThreads; ++i) {
        threads[i].join();
    }
    // get the best move of all threads
    int bestThreadIndex = 0;
    for (int i = 1; i < numberThreads; ++i) {
        if (scoreForEachThread[i] > scoreForEachThread[bestThreadIndex]) {
            bestThreadIndex = i;  
        }
    }
    //FIXME: end game best move seems to be to move king which is wrong
    AIMove = bestAIMoves[bestThreadIndex];

    numberThreads = tempNumberThreads;

    return AIMove;
}


float AI_Handler::findMoveNegaMaxAlphaBeta(GameState &gamestate, const std::vector<Move> &legalMoves, int depth, float alpha, float beta, int turnMultiplier, int threadIndex) {
    float currentScore;
    float maxScore = -checkmateScore;  // -CHECKMATE in Python
    float score;

    // Base case: if the depth is zero, evaluate the position
    if (depth == 0) {
        if (gamestate.m_checkmate) {
            currentScore = checkmateScore * turnMultiplier;
        //FIXME: if enabled AI makes stalemates moves in good positions for itself (but also without)
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
        score = -findMoveNegaMaxAlphaBeta(gamestate, localLegalMoves, depth - 1, -beta, -alpha, -turnMultiplier, threadIndex);

        // Undo the move
        undoMove(gamestate);

        // Update maxScore
        if (score > maxScore) {
            maxScore = score;
            if (depth == searchDepth) {  // Replace DEPTH with searchDepth or the appropriate depth variable
                bestAIMoves[threadIndex] = move;
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



Timer::Timer() {
    startTimePoint = std::chrono::high_resolution_clock::now();
}


Timer::~Timer() {
    auto endTimePoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration * 0.001;  // Convert microseconds to milliseconds

    std::cout << "Timer took " << ms << " ms" << std::endl;
}