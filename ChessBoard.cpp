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
	cb_map[position]=NULL;
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
	Pawn *p = new Pawn ("Pawn", colour);
	cb_map[position]=p;
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
	    cb_map[position]=r;
	  }
	if (file=='B'||file=='G')
	  {
	    Knight *k = new Knight ("Knight",colour);
	    cb_map[position]=k;
	  }
	if (file=='C'||file=='F')
	  {
	    Bishop *b = new Bishop ("Bishop",colour);
	    cb_map[position]=b;
	  }
	if (file=='D')
	  {
	    Queen *q = new Queen ("Queen",colour);
	    cb_map[position]=q;
	  }
	if (file=='E')
	  {
	    King *k = new King ("King",colour);
	    cb_map[position]=k;
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
  for(it = cb_map.begin(); it != cb_map.end(); ++it) 
    {
      if (it -> second != NULL) 
	delete it -> second;     
    }
  cb_map.clear();
}


ChessPiece* ChessBoard::getPos(string position)
{

  return cb_map[position];
}


/* Test if the move is out of board */
bool ChessBoard::outBoard(string position) 
{

  if ((position[0]>'H'||position[0]<'A')||(position[1]>'8'||position[1]<'1')) {
    cout << "There is no position " <<position<<" on ChessBoard!"<<endl;
    return true;
  }
  else 
    return false;
}


/* Check the move is valid and then excute the move */
void ChessBoard::submitMove(string src, string des)
{  
  bool cb_test = true;

  string curColour, curName;


  /********** MOVE OUT OF CHESS BOARD **********/
  if (outBoard(src)||outBoard(des))
    cb_test = false;

  /********** POSITION OCCUPIED **********/
  if (cb_map[src]==NULL){
    cb_map[des]=NULL;
    cout << "There is no piece at position "<< src <<"!"<<endl;
    cb_test = false;
  }

  else {
    curColour = cb_map[src]->getColour();
    curName = cb_map[src]->getName();

    /********** WRONG PLAYER **********/
    if ( curColour != nextColour ) {
      cout << "It is not "<< curColour <<"'s turn to move!"<<endl;
      cb_test = false;
    }

    else if(cb_map[des] != NULL) {

      string desColour = cb_map[des]->getColour();
      string desName = cb_map[des]->getName();
      
      /********** DESTINATION OCCUPIED BY THE SAME COLOUR **********/
      if (curColour.compare(desColour)==0) {
	cout << des << " is occupied by "<< desColour <<"'s "<<desName << endl;
	cout << curColour << "'s " << curName <<" cannot move to " << des << "!" << endl;
	cb_test = false;
      }
    }
  }
  
  if(cb_test) {
   
    /********** VALID MOVE: UPDATE CHESS BOARD **********/
    if( cb_map[src]->validMove(src, des, this) ){

      cb_map[src]->commitMove();    
      updateMap(src, des);

    }    
    /********** INVALID MOVE FOR THE PIECE TYPE **********/	
    else
      cout << curColour << "'s " << curName <<" cannot move to " << des << "!" << endl;     
  } 
}


void ChessBoard::updateMap(string src, string des) 
{

  string piece_name = cb_map[src]->getName();
 
  string piece_colour = cb_map[src]->getColour();
 
  
  /********** VALID MOVE **********/
  cout << piece_colour<< "'s " << piece_name<< " moves from " << src << " to " << des ;

  if (cb_map[des] != NULL) {
    string opp_colour = cb_map[des]->getColour();
    string opp_name = cb_map[des]->getName();

    /********** TAKING PIECE **********/
    cout << " taking " << opp_colour << "'s " << opp_name;
    delete cb_map[des];
    cb_map.erase(des);

  }
    cout<<endl;
    cb_map[des] = cb_map[src];
    cb_map[src] = NULL;
  
    /********** SWITCH PLAYER & TEST IN CHECK **********/
  
    if (piece_colour.compare("White")==0) {
   
      if (inCheck("Black")){

	if (stalemate("Black"))
	  cout << "Black is in checkmate" <<endl;
      
	else  
	  cout << "Black is in check" <<endl;
      }
     
      else if (stalemate("Black")){
	cout << "The Game is a Stalemate" << endl;
      }
    
      // Switch the player after the in check test 
      nextColour.assign("Black");
    }

    else {
    
      if (inCheck("White")){
     
	if (stalemate("White"))
	  cout << "White is in checkmate" <<endl;
     
	else
	  cout << "White is in check"<<endl;
      }

      else if (stalemate("White")){
	cout << "The Game is a Stalemate" << endl;
      }
      // Switch the player after the in check test 
      nextColour.assign("White");
    }  
 
}

/* Check whether the king is under immediate attack by the opponent's pieces */
bool ChessBoard::inCheck(string opp_colour) 
{
  map<string,ChessPiece*>::iterator it;
 
  // Find the position of King
  for (it = cb_map.begin(); it != cb_map.end(); ++it) {
    if(it->second != NULL) {
      if ((opp_colour.compare(it->second->getColour())==0)&&((it->second->getName()).compare("King")==0)) 
	KingPos = it -> first;
    }
  }
  // Check if there are any pieces can move to the King's position
  for (it = cb_map.begin(); it != cb_map.end(); ++it) {
    if(it -> second != NULL) {

      //Before we finish in check tesing, the nextcolour is still the current player
      if (nextColour.compare(it->second->getColour())==0) {	   
	   
	if(it -> second -> validMove(it->first, KingPos, this))
	  {	
	    attackingPos = it->first;
	    attackingName = it->second -> getName();	
	    return true;
	  }	    
      }
    }
  }
    
  return false;
}


/* For each piece, search every possible destination to check whether the king is still under immediate attack */
bool ChessBoard::stalemate(string opp_colour)
{
  map<string,ChessPiece*>::iterator itSrc, itDes;
  bool in_check = false;
  ChessPiece* takenPiece = NULL;
 
  //find the possible destination for each piece, which could result a in check. if we have a valid move, execute the move and then undo it 
  for (itSrc = cb_map.begin(); itSrc != cb_map.end(); ++itSrc) {
    for (itDes =cb_map.begin(); itDes != cb_map.end(); ++itDes) {

      if(itSrc -> second != NULL && (itSrc -> second ->getColour().compare(opp_colour)==0))
	{
	  if(itSrc -> second -> validMove(itSrc->first, itDes->first, this) && 
	     (itDes->second == NULL || 
	      itDes->second->getColour().compare(opp_colour) != 0)){
	    //temporarily store the taken piece
	    takenPiece = itDes->second;

	    cb_map[itDes->first] = cb_map[itSrc->first];
	    cb_map[itSrc->first] = NULL;

	    in_check = inCheck(opp_colour);
	    //undo the move
	    cb_map[itSrc->first] = cb_map[itDes->first];
	    cb_map[itDes->first] = takenPiece;
	    
	    if(!in_check) {	     
	      return false;
	    }
	  }	    
	}
    }
  }

  return true;
} 











