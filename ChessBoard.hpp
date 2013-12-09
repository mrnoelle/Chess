#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <string>
#include "ChessPiece.hpp"

using namespace std;

class ChessBoard {

 private:
  char rank;
  char file;
  string nextColour;
  string KingPos;
  string attackingPos;
  string attackingName;	
  map<string, ChessPiece*> cb_map;
 
 public: 
  ChessBoard();
  void resetBoard();
  void removePieces();
  ChessPiece* getPos(string position);
  bool outBoard(string position);
  void submitMove(string src, string des);
  void updateMap(string src, string des);  
  bool inCheck(string opp_colour);
  bool stalemate(string opp_colour);

};

#endif
