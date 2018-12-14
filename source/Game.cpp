// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"
#include "Game.h"

void Game::startNewGame( Board& board, WinConsole& console ){

  console.setFont( BoardGlobals::getSize() > 40 ? 2 : 9 );

  // OK as long as the Game object isn't const.
  Game* pgame = const_cast<Game*>(this);

  Player player1( "Jeeves",  &board, pgame, headsOrTailsColor() );
  Player player2( "Wooster", &board, pgame, player1 );
  Player* white = player1.getColor() == PieceColor::WHITE ? &player1 : &player2;
  Player* black = player2.getColor() == PieceColor::BLACK ? &player2 : &player1;

  console.showBoard( board );
  std::cout <<  "'-' '+' to change speed,\n"
                "'n' to start new game,\n"
                "'z' 'x' to change board size dynamically.\n"
                "Choose scenario 1 - 8 to start:                 Pieces codes:\n"
                "1 Classic game                                  1 Pawn\n"
                "2 Knight VS Rook                                3 Knight\n"
                "3 Queens Battle                                 4 Bishop\n"
                "4 Pawns Battle                                  5 Rook\n"
                "5 Bishop VS Pawn                                9 Queen\n"
                "6 Bishop VS Knight                              \x05 King\n"
                "7 Bishop VS Rook\n"
                "8 Random Battle";

  char ch = _getch();

  player1.arrangePieces( ch - 48 );

  while( isRunning() ){

    if( !white->makeRandomTestMove() ){
      std::cout << "\n" << white->getName()
      << " have no pieces or no moves. "
         "Press ANY KEY to let opponent to move instead.";
      _getch() ;
    }

    console.showBoard( board );
    console.showPlayerData( board, *white );
    console.controlKeyboard( board, player1, *pgame, console );

    if( !black->makeRandomTestMove() ){
      std::cout << "\n" << black->getName()
      << " have no pieces or no moves. "
         "Press ANY KEY to let opponent to move instead.";
      _getch() ;
    }

    console.showBoard( board );
    console.showPlayerData( board, *black );
    console.controlKeyboard( board, player1, *pgame, console );

    nextTurn();
  }

  _getch();
}
