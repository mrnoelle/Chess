#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
using namespace std;

class ChessBoard;

class ChessPiece 
{

 protected:
  string name;
  string colour;
  bool firstMove;

 public: 
  ChessPiece(string piece_name, string piece_colour);
  virtual ~ChessPiece();
  string getName() const;
  string getColour() const;
  virtual bool validMove(string current, string next, ChessBoard* board)=0;
  void commitMove(); 
};


#endif
