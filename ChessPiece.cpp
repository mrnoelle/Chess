#include "ChessPiece.hpp"

using namespace std;

ChessPiece::ChessPiece(string piece_name, string piece_colour) 
{
  name = piece_name;
  colour = piece_colour;
  firstMove = true;
}

ChessPiece::~ChessPiece()
{

}

string ChessPiece::getName() const 
{

  return name;
}

string ChessPiece::getColour() const 
{

  return colour;
}


void ChessPiece::commitMove()
{
  if(firstMove)
    firstMove = false;

}
