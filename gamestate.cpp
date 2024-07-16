#include "gamestate.h"


// Constructor implementation
GameState::GameState(): m_whitesTurn(true){
    // Iterate over the board to initialize list of pieces
    for (int row = 0; row < 8; ++row){
        for (int columm = 0; columm < 8; ++columm){
            int piece = m_chessBoard[row][columm];
            // Check if the piece is white
            if (m_chessBoard[columm][row]>20){
                PieceInfo whitePiece = { columm, row, piece };
                m_whitePieces.push_back(whitePiece);
            }
            // Check if the piece is black
            else if (m_chessBoard[columm][row] > 0 && m_chessBoard[columm][row] < 20){
                PieceInfo blackPiece = { columm, row, piece };
                m_blackPieces.push_back(blackPiece);
            }
        }
    }
}



bool GameState::isPieceTurn(int columm, int row){
    //whites turn and piece is white
    if(m_chessBoard[columm][row]>20 && m_whitesTurn){
        return true;
    }
    //blacks turn and piece is black
    else if(m_chessBoard[columm][row] > 0 && m_chessBoard[columm][row] < 20 && !m_whitesTurn){
        return true;
    }
    else{
        return false;
    }
}