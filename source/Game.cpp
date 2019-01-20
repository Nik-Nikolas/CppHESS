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

  /*
  char ch;
  std::cout <<  "\n1 Player1 - user game"
                "\n2         - simulations (C-Life game RANDOM)"
                "\n3         - simulations (C-Life game ORDERED): ";
  ch = _getch();
  // Pointer to class Player member function
  bool ( Player::* whitePlayer )( int32_t&, int32_t&, int32_t&, int32_t& );

  if( ch - 48 == 1 )
    whitePlayer = &Player::makeManualMove;
  else if( ch - 48 == 2 )
    whitePlayer = &Player::makeRandomTestMove;
  else
    whitePlayer = &Player::makeMove;
  std::cout << "\n";
  std::cout <<  "\n1 Player2 - user game"
                "\n2         - simulations (C-Life game RANDOM)"
                "\n3         - simulations (C-Life game ORDERED): ";
  ch = _getch();
  // Pointer to class Player member function
  bool ( Player::* blackPlayer )( int32_t&, int32_t&, int32_t&, int32_t& );

  if( ch - 48 == 1 )
    blackPlayer = &Player::makeManualMove;
  else if( ch - 48 == 2 )
    blackPlayer = &Player::makeRandomTestMove;
  else
    blackPlayer = &Player::makeMove;
    */

  const Strategy1 userGame;    // user game
  const Strategy2 randomGame;  // C-Life game RANDOM
  const Strategy3 orderedGame; // C-Life game ORDERED

  char ch;
  std::cout <<  "\nWHITES 1 user game"
                "\n       2 simulations (C-Life game RANDOM)"
                "\n       3 simulations (C-Life game ORDERED): ";
  ch = _getch();

  if( ch - 48 == 1 )
    white->setStrategy( &userGame );
  else if( ch - 48 == 2 )
    white->setStrategy( &randomGame );
  else
    white->setStrategy( &orderedGame );

  std::cout << "\n";
  std::cout <<  "\nBLACKS 1 user game"
                "\n       2 simulations (C-Life game RANDOM)"
                "\n       3 simulations (C-Life game ORDERED): ";
  ch = _getch();
  if( ch - 48 == 1 )
    black->setStrategy( &userGame );
  else if( ch - 48 == 2 )
    black->setStrategy( &randomGame );
  else
    black->setStrategy( &orderedGame );

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

  ch = _getch();
  player1.arrangePieces( ch - 48 );

  int32_t i, j, i2, j2;
  i = j = i2 = j2 = -1;
  bool frameIsShown = false;
  int32_t frameStep = 0;

  console.showBoard( board );

  while( isRunning() ){

    frameStep = BoardGlobals::getFramesStep();
    frameIsShown =
    !static_cast<bool>( game->currentTurn() % frameStep );

    //if( !( white->*whitePlayer )( i, j, i2, j2 ) ){
    if( !white->useStrategy( i, j, i2, j2 ) ){

      console.showBoard( board );
      console.showPlayerData( *black );

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
      console.showPlayerData( *white );
    }

    console.controlKeyboard( board, player1, *game, console );

    //if( !( black->*blackPlayer )( i, j, i2, j2 ) ){
    if( !black->useStrategy( i, j, i2, j2 ) ){

      console.showBoard( board );
      console.showPlayerData( *white );

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
    else if( frameIsShown &&
             frameStep == 1 ){ // Visualize board and data each 1 of m frames

      console.showBoard( board );
      console.showPlayerData( *black );
    }

    console.controlKeyboard( board, player1, *game, console );

    nextTurn();
  }

  _getch();
}
