// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"
#include "Game.h"

void Game::startNewGame( Board& board, WinConsole& console ){

  //console.setFont( BoardGlobals::getSize() > 40 ? 2 : 9 );

  // OK as long as the Game object isn't const.
  Game* game = const_cast<Game*>(this);

  Player player1( "Jeeves",  &board, game, headsOrTailsColor() );
  Player player2( "Wooster", &board, game, player1 );
  Player* white = player1.getColor() == PieceColor::WHITE ? &player1 : &player2;
  Player* black = player2.getColor() == PieceColor::BLACK ? &player2 : &player1;

  console.showBoard( board );
  std::cout <<  "1 Classic game\n"
                "2 Knight VS Rook\n"
                "3 Queens Battle\n"
                "4 Pawns Battle\n"
                "5 Bishop VS Pawn\n"
                "6 Bishop VS Knight\n"
                "7 Bishop VS Rook\n"
                "8 Random Battle\n"
                "'c' 'v' to change speed;   'a' 's' to change frame\n"
                "'n'     to start new game; 'z' 'x' to change board size\n"
                "'t'     to switch graphic mode to glyph / text";

  char ch = _getch();
  player1.arrangePieces( ch - 48 );

  int32_t i, j, i2, j2;
  i = j = i2 = j2 = -1;
  bool frameIsShown = false;
  while( isRunning() ){

    frameIsShown =
    !static_cast<bool>( game->currentTurn() % BoardGlobals::getFramesStep() );

    if( !white->makeRandomTestMove( i, j, i2, j2 ) ){

      console.showBoard( board );
      console.showPlayerData( board, *black );

      std::cout << "\n" << white->getName()
      << " have no pieces or no moves."
         " Press ANY KEY to START NEW GAME.";
      _getch();

      board.clearBoard();
      board.resetLastMovedPiece();
      board.resizeBoard();

      game->reset();
      game->startNewGame( board, console );
    }
    else if( frameIsShown ){ // Visualize board and data each 1 of m frames

      console.showBoard( board );
      console.showPlayerData( board, *white );
    }

    console.controlKeyboard( board, player1, *game, console );

    if( !black->makeRandomTestMove( i, j, i2, j2 ) ){

      console.showBoard( board );
      console.showPlayerData( board, *white );

      std::cout << "\n" << black->getName()
      << " have no pieces or no moves."
         " Press ANY KEY to START NEW GAME.";
      _getch();

      board.clearBoard();
      board.resetLastMovedPiece();
      board.resizeBoard();

      game->reset();
      game->startNewGame( board, console );
    }
    else if( frameIsShown ){ // Visualize board and data each 1 of m frames

      console.showBoard( board );
      console.showPlayerData( board, *black );
    }

    console.controlKeyboard( board, player1, *game, console );

    nextTurn();
  }

  _getch();
}
