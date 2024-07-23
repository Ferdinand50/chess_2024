#include "gamestate.h"
<<<<<<< HEAD


// Constructor implementation
GameState::GameState(): m_whitesTurn(true){
    //TODO: use this to keep track of pieces
    // Iterate over the board to initialize list of pieces currently no use
    // for (int y = 0; y < 8; ++y){
    //     for (int x = 0; x < 8; ++x){
    //         int piece = m_chessBoard[row][columm];
    //         // Check if the piece is white
    //         if (m_chessBoard[columm][row]>20){
    //             PieceInfo whitePiece = { columm, row, piece };
    //             m_whitePieces.push_back(whitePiece);
    //         }
    //         // Check if the piece is black
    //         else if (m_chessBoard[columm][row] > 0 && m_chessBoard[columm][row] < 20){
    //             PieceInfo blackPiece = { columm, row, piece };
    //             m_blackPieces.push_back(blackPiece);
    //         }
    //     }
    // }
}



bool GameState::isPieceTurn(int x, int y) const{
    //whites turn and piece is white
    if(m_chessBoard[y][x]>20 && m_whitesTurn){
        return true;
    }
    //blacks turn and piece is black
    else if(m_chessBoard[y][x] > 0 && m_chessBoard[y][x] < 20 && !m_whitesTurn){
        return true;
    }
    else{
        return false;
    }
}
=======
#include <iostream>

// Constructor implementation
GameState::GameState(){}

>>>>>>> 6083e5b (Initial commit)
