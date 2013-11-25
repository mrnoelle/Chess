#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Pawn.hpp"

Pawn::Pawn (string _name, string _colour, bool _firstMove): ChessPiece(_name, _colour) 
{
  firstMove = _firstMove;
}

Pawn::~Pawn() {}

bool Pawn::validMove(string current, string next, ChessBoard* board)
{
  bool pawnState = false;
  ChessPiece* next_position = board->getPos(next);

  /* move forward */
  if (colour.compare("White")==0) {
    file_change = (int)(next[0]-current[0]);
    rank_change = (int)(next[1]-current[1]);
  }
  else {
    file_change = (int)(current[0]-next[0]);
    rank_change = (int)(current[1]-next[1]);
  }
  
  /* valid move test */
  if (next_position == NULL) {
    /* CASE 1: move forward to the unoccupied square along the file */
    if (file_change==0 && rank_change==1) {
       pawnState = true;
    }
    /* CASE 2: for the first move, move forward two squares along the file if both are unoccupied */
    else if (firstMove && file_change==0 && rank_change==2) {
      string position;
      position += current[0];
      position += (char)(min(current[1],next[1])+1);
      
      if (board->getPos(position) == NULL)
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
