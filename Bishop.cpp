#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(string piece_name, string piece_colour): ChessPiece(piece_name, piece_colour) 
{

}

Bishop::~Bishop(){}

bool Bishop::validMove(string src, string des, ChessBoard* board) 
{

  file_change = abs((int)(des[0]-src[0]));
  rank_change = abs((int)(des[1]-src[1]));
   
  /* move any number of squares diagonally */
  if (!(rank_change > 0 && rank_change==file_change))   
    return false;
  
  /* test no leap over */
  else if (rank_change > 1 && rank_change == file_change) {

  int file_dir = (int)(des[0]-src[0])/file_change;
  int rank_dir = (int)(des[1]-src[1])/file_change;
  string pos = src;

    for (int i = 1; i < file_change; i++) {
      
      pos[0] = src[0] + file_dir*i;
      pos[1] = src[1] + rank_dir*i;
      if ( board-> getPos(pos) != NULL)
	return false;
    }
  } 
  else
    return true;
}
