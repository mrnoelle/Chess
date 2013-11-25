Chess: ChessMain.o ChessBoard.o ChessPiece.o King.o Rook.o Bishop.o Queen.o Knight.o Pawn.o
	g++ -Wall -g ChessMain.o ChessBoard.o ChessPiece.o King.o Rook.o Bishop.o Queen.o Knight.o Pawn.o -o Chess

ChessMain.o: ChessMain.cpp ChessBoard.hpp ChessPiece.hpp King.hpp Rook.hpp Bishop.hpp Queen.hpp Knight.hpp Pawn.hpp
	g++ -Wall -c -g ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessPiece.hpp King.hpp Rook.hpp Bishop.hpp Queen.hpp Knight.hpp Pawn.hpp
	g++ -Wall -c -g ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.hpp
	g++ -Wall -c -g ChessPiece.cpp

King.o: King.cpp ChessPiece.hpp King.hpp
	g++ -Wall -c -g King.cpp

Rook.o: Rook.cpp ChessPiece.hpp Rook.hpp
	g++ -Wall -c -g Rook.cpp

Bishop.o: Bishop.cpp ChessPiece.hpp Bishop.hpp
	g++ -Wall -c -g Bishop.cpp

Queen.o: Queen.cpp ChessPiece.hpp Queen.hpp
	g++ -Wall -c -g Queen.cpp

Knight.o: Knight.cpp ChessPiece.hpp Knight.hpp
	g++ -Wall -c -g Knight.cpp

Pawn.o: Pawn.cpp ChessPiece.hpp Pawn.hpp
	g++ -Wall -c -g Pawn.cpp

clean:
	rm -f ChessMain *.o