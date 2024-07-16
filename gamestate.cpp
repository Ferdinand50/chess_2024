#include "gamestate.h"
#include <iostream>

// Constructor implementation
GameState::GameState(): m_whitesTurn(true){

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