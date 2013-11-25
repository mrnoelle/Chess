#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include "ChessPiece.hpp"

//enum Colour {White, Black};

class ChessBoard {

 private:
  char rank;
  char file;

  string nextColour;
	
  map<string, ChessPiece*> cb_state;
 

 public:
 
  ChessBoard();
  void resetBoard();
  void removePieces();

  void printBoard();
 
  ChessPiece* getPos(string position);

  bool outBoard(string position);
  void submitMove(string curPos, string newPos);
  void updateState(string curPos, string newPos); 

  //int inCheck(string oppCol);
};

#endif
