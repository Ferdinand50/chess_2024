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
    int temp_score;

    //TODO: implement postion score of pieces
    //evaluate the board
   for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            piece = gamestate.m_chessBoard[y][x];
            //piece detected
            if(piece!=EMPTY){
                temp_score = PieceScoreMap[piece];
                //white pieces have a positive score
                if (temp_score>0)
                    whiteScore += temp_score;
                //black pieces have a negative score
                else 
                    blackScore += temp_score;
            }
        }
    }


    return whiteScore + blackScore;
}

// def returnScore(gs):

//     #evaluate the board
//     for rank in range(8):
//         for file in range(8):
//             #white pieces
//             if int(str(gs.board[rank][file])[0]) == 1:
//                 piece_name = IntToStringconverter(int(str(gs.board[rank][file])[1]))
//                 piece_score = PieceNameToPieceScoreconverter(piece_name)
//                 #position
//                 if piece_name == "Pawn":
//                     position_score = whitePawnMap[rank][file]
//                 if piece_name == "Rook":
//                     position_score = whiteRookMap[rank][file]
//                 if piece_name == "Knight":
//                     position_score = whiteKnightMap[rank][file]
//                 if piece_name == "Bishop":
//                     position_score = whiteBishopMap[rank][file]
//                 if piece_name == "Queen":
//                     position_score = whiteQueenMap[rank][file]
//                 if piece_name == "King":
//                     position_score = whiteKingMap[rank][file]
//                 white_score = white_score + piece_score + position_score * POSITION_WEIGHT
//             #black pieces
//             elif int(str(gs.board[rank][file])[0]) == 2:
//                 piece_name = IntToStringconverter(int(str(gs.board[rank][file])[1]))
//                 piece_score = PieceNameToPieceScoreconverter(piece_name)
//                 #position
//                 if piece_name == "Pawn":
//                     position_score = blackPawnMap[rank][file]
//                 if piece_name == "Rook":
//                     position_score = blackRookMap[rank][file]
//                 if piece_name == "Knight":
//                     position_score = blackKnightMap[rank][file]
//                 if piece_name == "Bishop":
//                     position_score = blackBishopMap[rank][file]
//                 if piece_name == "Queen":
//                     position_score = blackQueenMap[rank][file]
//                 if piece_name == "King":
//                     position_score = blackKingMap[rank][file]
//                 black_score = black_score + piece_score  + position_score * POSITION_WEIGHT
//     score = white_score - black_score
//     return score