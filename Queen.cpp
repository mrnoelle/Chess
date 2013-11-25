#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Queen.hpp"

Queen::Queen (string _name, string _colour): ChessPiece(_name, _colour) 
{

}

Queen::~Queen() {}


bool Queen::validMove(string current, string next, ChessBoard* board) 
{

  file_change = abs((int)(next[0]-current[0]));
  rank_change = abs((int)(next[1]-current[1]));
 
  if (!((file_change==0 && rank_change>0)||(file_change>0 && rank_change==0)||(rank_change>0 && rank_change==file_change ))) {
    return false;
  }
 
  /* test no leap over */
  /* CASE 1: move along a rank */
  else if (file_change==0 && rank_change>1) {
    for (char i=(char)(min(current[1],next[1])+1); i<max(current[1],next[1]); i++) {
      string position;
      position += current[0];
      position += i;
      if (board->getPos(position) != NULL)
	return false;
    }
    return true;
  }
  /* CASE 2: move along a file */
  else if(rank_change==0 && file_change>1){
    for (char i=(char)(min(current[0],next[0])+1); i<max(current[0],next[0]); i++) {
      string position;
      position += i;
      position += current[1];
      if (board->getPos(position) != NULL)
	return false;
    }
    return true;
  }
  /* CASE 3: move diagonally */
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
  else {
    return true;
  }
}
