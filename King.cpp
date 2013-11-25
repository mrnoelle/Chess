#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "King.hpp"

King::King(string _name, string _colour): ChessPiece(_name, _colour)
{

}

King::~King(){}

bool King::validMove(string current, string next, ChessBoard* board) 
{

  file_change = abs((int)(next[0]-current[0]));
  rank_change = abs((int)(next[1]-current[1]));

  /* move one square in any direction */
  if ((file_change==1 && rank_change==0)||(file_change==0 && rank_change==1)||(file_change==1 && rank_change==1)) 
    return true;
  else 
    return false;
}
