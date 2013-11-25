#include<iostream>
#include<string>
#include<cmath>
using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"

ChessPiece::ChessPiece(string _name, string _colour) 
{
  name = _name;
  colour = _colour;
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


