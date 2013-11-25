#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(string _name, string _colour): ChessPiece(_name, _colour) 
{

}

Bishop::~Bishop(){}

bool Bishop::validMove(string current, string next, ChessBoard* board) 
{

  file_change = abs((int)(next[0]-current[0]));
  rank_change = abs((int)(next[1]-current[1]));
  
  /* move any number of squares diagonally */
  if (!(rank_change>0 && rank_change==file_change))
    return false;
  /* test no leap over */
  else if (rank_change >1 && rank_change == file_change) {
    for (char i=(char)(min(current[0],next[0])+1); i<max(current[0],next[0]); i++) {
      for (char j=(char)(min(current[1],next[1])+1); j<max(current[1],next[1]); j++) {
	string position;
	position += i;
	position += j;
	if (board->getPos(position) != NULL)
	  return false;    
      }
    }
    return true;
  }
}
