#include "gamestate.h"


// Constructor implementation
GameState::GameState(): m_whitesTurn(true), m_inCheck(false), m_checkmate(false), m_stalemate(false), m_whiteKingPosition({7, 4}), m_blackKingPosition({0, 4}){

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


void GameState::printBoard() const {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(m_chessBoard[y][x]!=0)
                std::cout << m_chessBoard[y][x] << ' ';
            else
                std::cout << "0 " << ' ';
        }
        std::cout << std::endl;
    }
    std::cout<<"-----------------------"<<std::endl;
}

