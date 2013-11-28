#include<iostream>
#include<string>
#include<cmath>
#include "Knight.hpp"

using namespace std;

Knight::Knight(string piece_name, string piece_colour): ChessPiece(piece_name, piece_colour) 
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
