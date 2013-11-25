#include<iostream>
#include<string>
#include<cmath>
#include<map>

using namespace std;

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "King.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"


ChessBoard:: ChessBoard() 
{

  resetBoard();
}


void ChessBoard:: resetBoard() 
{
  removePieces();
 
  string colour; 

  /* Set the unoccupied squares */
  for (rank='3'; rank <= '6'; rank++) {
    for (file='A'; file <= 'H'; file++)
      {
	string position;
	position += (file);
	position += (rank);
	cb_state[position]=NULL;
      }
  }
  


  /* Set Pawns for White and Black */ 
  for (rank = '2'; rank <='7'; rank +=5) {
    if (rank=='2')
      colour = "White";
    else 
      colour = "Black";
    for (file='A'; file<='H';file++)
      {
	string position;
	position +=(file);
	position +=(rank);
	Pawn *p = new Pawn ("Pawn",colour,true);
	cb_state[position]=p;
      }
  }

  
  /* Set other pieces for White and Black */
  for (rank='1'; rank <= '8'; rank += 7) {
    if (rank == '1')
      colour = "White";
    else
      colour = "Black";
	  
    for (file='A'; file <= 'H'; file++)
      {
	string position;
	position += (file);
	position += (rank);
	if (file=='A'||file=='H')
	  {
	    Rook *r = new Rook ("Rook",colour);
	    cb_state[position]=r;
	  }
	if (file=='B'||file=='G')
	  {
	    Knight *k = new Knight ("Knight",colour);
	    cb_state[position]=k;
	  }
	if (file=='C'||file=='F')
	  {
	    Bishop *b = new Bishop ("Bishop",colour);
	    cb_state[position]=b;
	  }
	if (file=='D')
	  {
	    Queen *q = new Queen ("Queen",colour);
	    cb_state[position]=q;
	  }
	if (file=='E')
	  {
	    King *k = new King ("King",colour);
	    cb_state[position]=k;
	  }
      }
  }
    
  nextColour = "White";
  /********************* GAME START ***********************/
  cout << "A new chess game is started!"<<endl;
}


void ChessBoard::removePieces()
{
  map<string, ChessPiece*>::iterator it;
  for(it = cb_state.begin(); it != cb_state.end(); ++it) 
    {
      if (it -> second != NULL) 
	delete it -> second;
      
    }
}



void ChessBoard::printBoard() 
{

  map<string, ChessPiece*>::iterator it;
  for(it = cb_state.begin(); it != cb_state.end(); ++it)
    {
     
      if (it -> second != NULL) 
	{
	  string piece_name = (it->second) -> getName();
	  string piece_colour = (it->second) -> getColour();

	if (piece_colour=="White") {
	  if (piece_name=="King")
        cout << "   w*";
	  else 
	    cout << "   w" << piece_name[0];
	}
	else {
	  if (piece_name=="King")
        cout << "   b*";
	  else 
	    cout << "   b" << piece_name[0];
	}
      }
      else 
	cout << "   " << "__";

      if (it->first[1] == '8')
	cout << endl;
    }
  cout << endl<<endl;
}




ChessPiece* ChessBoard::getPos(string position)
{

  return cb_state[position];
}




bool ChessBoard::outBoard(string position) 
{

  if ((position[0]>'H'||position[0]<'A')||(position[1]>'8'||position[1]<'1')) {
    cout << "There is no position " <<position<<" on ChessBoard!"<<endl;
    return true;
  }
  else 
    return false;
}





void ChessBoard::submitMove(string curPos, string newPos)
{  
  bool cb_test = true;

  string curColour, curName;

  /********** MOVE OUT OF CHESS BOARD **********/
  if (outBoard(curPos)||outBoard(newPos))
    cb_test = false;

  /********** POSITION OCCUPIED **********/
  if (cb_state[curPos]==NULL){
    cb_state[newPos]=NULL;
    cout << "There is no piece at position "<<curPos<<"!"<<endl;
    cb_test = false;
  }

  else {
    curColour = cb_state[curPos]->getColour();
    curName = cb_state[curPos]->getName();

    /********** NOT YOUR TURN **********/
    if ( curColour != nextColour ) {
      cout << "It is not "<<curColour<<"'s turn to move!"<<endl;
      cb_test = false;
    }

    else if(cb_state[newPos] != NULL) {

      string desColour = cb_state[newPos]->getColour();
      string desName = cb_state[newPos]->getName();
      
      /********** DESTINATION OCCUPIED BY THE SAME COLOUR **********/
      if (curColour.compare(desColour)==0) {
	cout << newPos << " is occupied by "<< desColour <<"'s "<<desName << endl;
	cout << curColour << "'s " << curName <<" cannot move to " << newPos << "!" << endl;
	cb_test = false;
      }
    }
  }
  
  if(cb_test) {
    /********** VALID MOVE: UPDATE CHESS BOARD **********/
    if( cb_state[curPos]->validMove(curPos, newPos, this) )
      updateState(curPos, newPos);
    /********** INVALID MOVE FOR THE PIECE TYPE **********/	
    else
      cout << curColour << "'s " << curName <<" cannot move to " << newPos << "!" << endl;     
  } 
}



void ChessBoard::updateState(string curPos, string newPos) 
{

  string piece_name = cb_state[curPos]->getName();
  string piece_colour = cb_state[curPos]->getColour();
  /********** VALID MOVE **********/
  cout << piece_colour<< "'s " << piece_name<< " moves from " << curPos << " to " << newPos;

  if (cb_state[newPos] != NULL) {
    string opp_colour = cb_state[newPos]->getColour();
    string opp_name = cb_state[newPos]->getName();

    /********** TAKING PIECE **********/
    cout << " taking " << opp_colour << "'s " << opp_name << endl;
    delete cb_state[newPos];
  }
  else {
    cout << endl; 
    cb_state[newPos] = cb_state[curPos];
    cb_state[curPos] = NULL;
  }

  /********** TEST IN CHECK **********/
  /*
  if (piece_colour.compare("White")==0) {

    if (inCheck("Black") > 0){
      cout << "Black is in check"<<endl;
    }
    nextColour.assign("Black");
  }
  else {
    if (inCheck("White") > 0){
      cout << "White is in check"<<endl;
    }
    nextColour.assign("White");
  }  
  */
}













/*
int ChessBoard::inCheck(string opp_colour) {
  
  // find reference to oppCol's King

  map<string,ChessPiece*>::iterator it, KingAdd;
  for (it=cb_state.begin(); it != cb_state.end(); it++) {
    if(it->second !=NULL) {
      if ((opp_colour.compare(it->second->getColour())==0)&&((it->second->getName()).compare("King")==0)) 
	KingAdd = it;
    }
  }
  
  // test if the opponent's King is under immediate attack by the pieces of curCol
  // the "in-check" test is performed before the nextCol is updated, i.e. curCol==nextCol
  int attacking_pieces = 0;
  
  for (it=cb_statetate.begin(); it != cb_state.end(); it++) {
    if (it->second != NULL) {
      if (nextColour.compare(it->second->getColour())==0) {
	if (it->second->validMove((it->first),(KingAdd->first), this)) 
	  attacking_pieces++;
      }
    }
  }
  return attacking_pieces;
}

*/
