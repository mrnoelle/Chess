#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Pawn.hpp"

Pawn::Pawn (string piece_name, string piece_colour, bool _firstMove): ChessPiece(piece_name, piece_colour) 
{
  firstMove = _firstMove;
}

Pawn::~Pawn() {}

bool Pawn::validMove(string src, string des, ChessBoard* board)
{
  bool pawnState = false;
  ChessPiece* next_position = board->getPos(des);

  /* move forward */
  if (colour.compare("White")==0) {
    file_change = (int)(des[0]-src[0]);
    rank_change = (int)(des[1]-src[1]);
  }
  else {
    file_change = (int)(src[0]-des[0]);
    rank_change = (int)(src[1]-des[1]);
  }
  
  /* valid move test */
  if (next_position == NULL) {
    /* CASE 1: move forward to the unoccupied square along the file */
    if (file_change==0 && rank_change==1) {
       pawnState = true;
    }
    /* CASE 2: for the first move, move forward two squares along the file if both are unoccupied */
    else if (firstMove && file_change==0 && rank_change==2) {
      string pos;
      pos += src[0];
      pos += (char)(min(src[1],des[1])+1);
      
      if (board->getPos(pos) == NULL)
	  pawnState = true; 
    }
  }
  /* CASE 3: move to the diagonal square if it's occupied by opponent's piece */
  else if (abs(file_change)==1 && abs(rank_change==1)) {
    pawnState = true;
  }
  /* set flag "firstMove" to false after a valid move */
  if (firstMove && pawnState) {
    firstMove = false;
  }
  return pawnState;
}
