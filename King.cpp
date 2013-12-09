#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "King.hpp"

King::King(string piece_name, string piece_colour): ChessPiece(piece_name, piece_colour)
{

}

King::~King(){}

bool King::validMove(string src, string des, ChessBoard* board) 
{

  int file_change = abs((int)(des[0]-src[0]));
  int rank_change = abs((int)(des[1]-src[1]));

  /* move one square in any direction */
  if ((file_change==1 && rank_change==0)||(file_change==0 && rank_change==1)||(file_change==1 && rank_change==1)) 
    return true;
  else 
    return false;
}
