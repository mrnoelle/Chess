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
	Pawn *p = new Pawn ("Pawn",colour,true);
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
}



void ChessBoard::printBoard() 
{

  map<string, ChessPiece*>::iterator it;
  for(it = cb_map.begin(); it != cb_map.end(); ++it)
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
	cout << endl << endl;

    }
  cout << endl << endl;
}




ChessPiece* ChessBoard::getPos(string position)
{

  return cb_map[position];
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
    //cb_map.erase(src);

 
    /********** SWITCH PLAYER & TEST IN CHECK **********/
  
  if (piece_colour.compare("White")==0) {
      
    if (inCheck("Black")){
      if (checkmate("Black")){
	cout << "Black is in checkmate" <<endl;
      }
      else
	cout << "Black is in check" <<endl;
    }
    nextColour.assign("Black");
  }

  else {
    if (inCheck("White")){
      if (checkmate("White")){
	cout << "White is in checkmate" <<endl;
      }
      else
	cout << "White is in check"<<endl;
    }

    nextColour.assign("White");
  }  
 
}




bool ChessBoard::inCheck(string opp_colour) 
{

  map<string,ChessPiece*>::iterator it;
  //string KingPos;

  /* Find the position of King */
  for (it = cb_map.begin(); it != cb_map.end(); ++it) {
    if(it->second != NULL) {
	if ((opp_colour.compare(it->second->getColour())==0)&&((it->second->getName()).compare("King")==0)) 
	  KingPos = it -> first;
      }
  }
 
  /* Check if there are any pieces can move to King's position */
    for (it = cb_map.begin(); it != cb_map.end(); ++it) {
      if(it -> second != NULL) {	 
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




bool ChessBoard::checkmate(string opp_colour)
{
  bool in_check = false;
  ChessPiece* temp_piece;

  //CASE 1: move the King 
  map<string,ChessPiece*>::iterator it;
  for (it = cb_map.begin(); it != cb_map.end(); ++it) {
    if (nextColour.compare(cb_map[KingPos]->getColour())==0) {
      if(cb_map[KingPos] -> validMove(KingPos, it->first, this)) {
	

	cb_map[it->first] = cb_map[KingPos];
	cb_map[KingPos] = NULL;
	in_check = inCheck(opp_colour);
	
	cb_map[KingPos] = cb_map[it->first];
	cb_map[it->first] = NULL;
	if(in_check) continue;
	else 
	  return false;
	
      }
    } 
  }
  
  //CASE 2: taking attacking piece
  for (it = cb_map.begin(); it != cb_map.end(); ++it) {
    if (nextColour.compare(cb_map[KingPos]->getColour())==0) {
      if(it->second -> validMove(it->first, attackingPos, this)) {
	temp_piece = cb_map[attackingPos];
	
	cb_map[attackingPos] = cb_map[it->first];
	cb_map[it->first] = NULL;
	in_check = inCheck(opp_colour);
	
	cb_map[it->first] = cb_map[attackingPos];
	cb_map[attackingPos] = temp_piece;
	if(in_check) continue;
	else 
	  return false;
      
      }  
    }  
  }
  
  //CASE 3: stop the move of attacking piece, if the piece is Queen, Bishop or Rook
  if(attackingName.compare("Queen")==0 ||
     attackingName.compare("Bishop")==0 ||
     attackingName.compare("Rook")==0) {
      
      int file_change = abs((int)(KingPos[0]-attackingPos[0]));
      int rank_change = abs((int)(KingPos[1]-attackingPos[1]));
   
 
      if ((rank_change > 1 || file_change > 1)) {
	  
	int file_dir = (int)(KingPos[0]-attackingPos[0])/file_change;
	int rank_dir = (int)(KingPos[1]-attackingPos[1])/file_change;

	string pos = KingPos;

	for (int i = 1; i < file_change && i< rank_change; i++)
	  {
      
	    pos[0] = KingPos[0] + file_dir*i;
	    pos[1] = KingPos[1] + rank_dir*i;

	    for (it = cb_map.begin(); it != cb_map.end(); ++it) {
	      if (nextColour.compare(cb_map[KingPos]->getColour())==0) {
		if(it->second -> validMove(it->first, pos, this)) {

		  cb_map[pos] = cb_map[it->first];
		  cb_map[it->first] = NULL;
		  in_check = inCheck(opp_colour);
	
		  cb_map[it->first] = cb_map[pos];
		  cb_map[pos] = NULL;
		  if(in_check) continue;
		  else 
		    return false;
      
		}  
	      }
	    }
	  } 
      }
    }

    return true;

}



/*
bool ChessBoard::checkmate(string opp_colour)
{
  map<string,ChessPiece*>::iterator itSrc, itDes;
  bool state = false;
  //ChessPiece* temp_piece;

 for (itSrc = cb_map.begin(); itSrc != cb_map.end(); ++itSrc) {
   for (itDes =cb_map.begin(); itDes != cb_map.end(); ++itDes) {

      if(itSrc -> second != NULL)
	{	 
	  if (nextColour.compare(itSrc->second->getColour())==0 && nextColour.compare(itDes->second->getColour())!= 0 )
	    {
	      if(itSrc -> second -> validMove(itSrc->first, itDes->first, this)){
		updateMap(itSrc, itDes);
		if( inCheck )
		state = true;
		undoMove(itSrc, itDes);
	      }
	    }
	}
    }
 }

} 


*/









