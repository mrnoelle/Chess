#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Rook.hpp"

Rook::Rook (string piece_name, string piece_colour): ChessPiece(piece_name, piece_colour) 
{

}

Rook::~Rook(){}

bool Rook::validMove(string current, string next, ChessBoard* board) 
{
  
  file_change = abs((int)(next[0]-current[0]));
  rank_change = abs((int)(next[1]-current[1]));
  
  /* move any number of squares along any rank or file */ 
  if (!((file_change==0 && rank_change>0) || (file_change>0 && rank_change==0))) {
    return false;
  }
 
  /* no leap over other pieces */
  /* CASE 1: move along a rank */
  else if (rank_change > 1) { 
  
    for (char i=(char)(min(current[1],next[1])+1); i < max(current[1],next[1]); i++) {
      string position;
      position += current[0];
      position += i;
      if (board -> getPos(position) != NULL)
	return false;
	
      }
  }
  /* CASE 2: move along a file */
  else {
    for (char i=(char)(min(current[0],next[0])+1); i<max(current[0],next[0]); i++) {
      string position;
      position += i;
      position += current[1];
      if (board->getPos(position) != NULL)
	return false;
    }
  }
  return true;
}

