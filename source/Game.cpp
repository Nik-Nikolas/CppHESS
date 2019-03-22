// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"
#include "Game.h"

Game::Game()
{
  // Set global settings
  BoardGlobals::setSize( ::START_BOARD_SIDE );
  BoardGlobals::setLongMoveStep( ::START_BOARD_SIDE / 2 );
  BoardGlobals::setDelay( ::START_DELAY );

  static_assert( ::START_BOARD_SIDE % 2 == 0,
                 "Board cells amount should be an even number.");

  board_ = new Board();
  winConsole_ = new WinConsole();
}

Game::~Game()
{
  delete board_;
  delete winConsole_;
}

void Game::start(){

  // First player plays headsOrTails game to choose pieces color
  Player player1( "Jeeves",  board_, this, headsOrTailsColor() );

  // Second player takes another color
  Player player2( "Wooster", board_, this, player1 );

  // Pointers to players
  Player* white = player1.getColor() == PieceColor::WHITE ? &player1 : &player2;
  Player* black = player2.getColor() == PieceColor::BLACK ? &player2 : &player1;

  /* BLOCK WITH Pointers to class Player member functions. Obsolete
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

  std::cout <<  "\nWHITES 1 user game"
                "\n       2 simulations (C-Life game RANDOM)"
                "\n       3 simulations (C-Life game ORDERED): ";

  setStrategy( white );

  std::cout << "\n";
  std::cout <<  "\nBLACKS 1 user game"
                "\n       2 simulations (C-Life game RANDOM)"
                "\n       3 simulations (C-Life game ORDERED): ";

  setStrategy( black );

  winConsole_->showBoard( *board_ );
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

  player1.arrangePieces();

  winConsole_->showBoard( *board_ );

  // Main game cycle
  while( isRunning() ){

    // WHITES play
    makeTurn( white, black, *winConsole_, *board_ );
    winConsole_->controlKeyboard( *board_, player1, *this, *winConsole_ );

    // BLACKS play
    makeTurn( black, white, *winConsole_, *board_ );
    winConsole_->controlKeyboard( *board_, player1, *this, *winConsole_ );

    nextTurn();
  }

  _getch();

  // Delete Random Device - we dont need it anymore
  RandomDevice::deleteInstance();
}

// Player makes turn in accordance with chosen strategy
void Game::makeTurn( Player* const player1,
                     const Player* const player2,
                     WinConsole& console,
                     Board& board ){

  int32_t i, j, i2, j2; // Coords before/after move.
  i = j = i2 = j2 = -1;

  int32_t frameStep = BoardGlobals::getFramesStep();
  bool frameIsShown = !static_cast<bool>( currentTurn() % frameStep );

  if( !player1->playStrategy( i, j, i2, j2 ) ){

    console.showBoard( board );
    console.showPlayerData( *player2 );

    std::cout << "\n" << player1->getName()
    << " have no pieces or no moves."
       " Press ANY KEY to START NEW GAME.";
    _getch();

    board.clear();
    board.resetLastMovedPiece();
    board.resize();

    this->reset(); // reset game
    this->start(); // start new game
  }
  else if( frameIsShown ){ // Visualize board and data each 1 of m frames

    if( frameStep == 1 ){
      console.showBoard( board );
      console.showPlayerData( *player1 );
    }
    // If frameStep > 1 - show only data after WHITE piece move to prevent
    // display similar board views
    else if( player1->getColor() == PieceColor::WHITE ){
      console.showBoard( board );
      console.showPlayerData( *player1 );
    }
  }
}

void Game::setStrategy( Player* player ){

  const char ch = _getch();

  const StrategyInterface* playerStrategy;
  switch( ch - 48 ){

    case 1  : playerStrategy = new Strategy1; break; // user game
    case 2  : playerStrategy = new Strategy2; break; // C-Life game RANDOM
    default : playerStrategy = new Strategy3; break; // C-Life game ORDERED
  }

  player->setStrategy( playerStrategy );
}

inline void Game::nextTurn(){
  ++turns_;

  if ( ::TURNS_MAX <= turns_ ){
    isValid_ = false;

    throw GameIsOver();
  }
}

void Game::reset(){
  turns_ = 0;
  isValid_ = true;
}

inline const bool Game::isRunning() const {
  return isValid_;
}

const int32_t Game::currentTurn() const{
  return turns_;
}

void Game::setTurn( const int32_t turns ){
  turns_ = turns;
}

//!< Heads or tails game - who plays white.
const PieceColor Game::headsOrTailsColor(){

  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( ( *rd )() );
  // give "true" 1/2 of the time
  // give "false" 1/2 of the time
  std::bernoulli_distribution d( 0.5 );

  return d( gen ) ? PieceColor::WHITE : PieceColor::BLACK;
}
