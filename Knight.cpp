#include<iostream>
#include<string>
#include<cmath>
#include "Knight.hpp"

using namespace std;

Knight::Knight(string piece_name, string piece_colour): ChessPiece(piece_name, piece_colour) 
{

}

Knight::~Knight() {}

bool Knight::validMove(string src, string des, ChessBoard* board) 
{
  
  int file_change = abs((int)(des[0]-src[0]));
  int rank_change = abs((int)(des[1]-src[1]));
  /* move forms an "L"-shape */
  if (!((file_change==1 && rank_change==2)||(file_change==2 && rank_change==1)))
    return false;
  else 
    return true;
}
