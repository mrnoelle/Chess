#include<iostream>
#include<string>
#include<cmath>

using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Knight.hpp"

Knight::Knight(string _name, string _colour): ChessPiece(_name, _colour) 
{

}

Knight::~Knight() {}

bool Knight::validMove(string current, string next, ChessBoard* board) 
{
  
  file_change = abs((int)(next[0]-current[0]));
  rank_change = abs((int)(next[1]-current[1]));
  /* move forms an "L"-shape */
  if (!((file_change==1 && rank_change==2)||(file_change==2 && rank_change==1)))
    return false;
  else 
    return true;
}
