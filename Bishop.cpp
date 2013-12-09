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
  int file_dir = 0;
  int rank_dir = 0;
  int file_change = abs((int)(des[0]-src[0]));
  int rank_change = abs((int)(des[1]-src[1]));
   
  /* move any number of squares diagonally */
  if ((rank_change == 0) || (rank_change!=file_change))   
    return false;
  
  /* test no leap over */
  if (file_change > 0)
    file_dir = (int)(des[0]-src[0])/file_change;

  if (rank_change > 0)
    rank_dir = (int)(des[1]-src[1])/rank_change;

  string pos = src;
  for (int i = 1; i < file_change || i < rank_change; i++) {
      
    pos[0] = src[0] + file_dir*i;
    pos[1] = src[1] + rank_dir*i;
    if ( board -> getPos(pos) != NULL)
      return false;
  }
  
  return true;
}
