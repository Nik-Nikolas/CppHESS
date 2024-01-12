// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file

#include "Console.h"
#include "Player.h"
#include "Game.h"

#include "StrategyManual.h"
#include "StrategyOrdered.h"
#include "StrategyRandom.h"
#include <cstdint>
#include <stdexcept>

Game::Game( std::shared_ptr<Board> board,
            std::shared_ptr<Console> Console,
            std::mutex* mainMutex ) : board_( board ),
                                                       console_( Console ),
                                                       mainMutex_ ( mainMutex ){}

void Game::start(){

  // First player plays headsOrTails game to choose pieces color
  Player player1( "Jeeves",  board_, shared_from_this(), headsOrTailsColor(), mainMutex_ );

  // Second player takes another color
  Player player2( "Wooster", board_, shared_from_this(), player1, mainMutex_ );

  // Players mapping to colors
  Player* white = player1.getColor() == PieceColor::WHITE ? &player1 : &player2;
  Player* black = player2.getColor() == PieceColor::BLACK ? &player2 : &player1;

  std::cout <<  "\nWHITES 1 user game"
                "\n       2 simulations (C-Life game RANDOM)"
                "\n       3 simulations (C-Life game ORDERED): ";

  setStrategy( white );

  std::cout << "\n";
  std::cout <<  "\nBLACKS 1 user game"
                "\n       2 simulations (C-Life game RANDOM)"
                "\n       3 simulations (C-Life game ORDERED): ";

  setStrategy( black );

  console_->showBoard( board_ );
  std::cout <<  "1 Classic game\n"
                "2 Knight VS Rook\n"
                "3 Queens Battle\n"
                "4 Pawns Battle\n"
                "5 Bishop VS Pawn\n"
                "6 Bishop VS Knight\n"
                "7 Bishop VS Rook\n"
                "8 Random Battle\n"
                "'c' 'v' to change speed;   'a' 's' to change frame\n"
                "'n'     to start a new game; 'z' 'x' to change board size\n"
                "'t'     to switch pieces representation to glyph / text";


  player1.arrangePieces();

  console_->showBoard( board_ );

  // Main game cycle
  while( true ){

    if(!isValid())
      break;

    // waitCertainKeyAsync(32);

    // WHITES play
    auto res = makeTurn( white, black );
    if(!res)
      break;

    // BLACKS play
    res = makeTurn( black, white );
    if(!res)
      break;

    nextTurn();
  }
}

// Player makes turn in accordance with chosen strategy
bool Game::makeTurn( Player* const player1,
                     const Player* const player2 ){

  if(!isValid())
    return false; 

  int32_t i, j, i2, j2; // Coords before/after move.
  i = j = i2 = j2 = -1;

  int32_t frameStep = BoardGlobals::getFramesStep();
  bool frameIsShown = !static_cast<bool>( currentTurn() % frameStep );

  if( !player1->playStrategy( i, j, i2, j2 ) ){

    console_->showBoard( board_ );
    console_->showPlayerData( *player2 );

    board_->clear();
    board_->resetLastMovedPiece();
    board_->resize();

    std::cout << "\n" << player1->getName()
    << " have no pieces or no moves.";

    setInvalid();
  }
  else if( frameIsShown ){ // Visualize board and data each 1 of m frames

    if( frameStep == 1 ){
      console_->showBoard( board_ );
      console_->showPlayerData( *player1 );
    }
    // If frameStep > 1 - show only data after WHITE piece move to prevent
    // display similar board views
    else if( player1->getColor() == PieceColor::WHITE ){
      console_->showBoard( board_ );
      console_->showPlayerData( *player1 );
    }
  }

  return isValid(); 
}

void Game::setStrategy( Player* player ){

  console_->setConsoleInputMode(ConsoleInputMode::SYNC);
  int32_t ch{};
  while(true){
      ch = ChoiceDevice::getInstanceAsync() - 48;
      if(ch >= 1 && ch <= 3)
        break;
  }
  console_->setConsoleInputMode(ConsoleInputMode::ASYNC);

  const StrategyInterface* playerStrategy;
  switch( ch ){

    case 1  : playerStrategy = new StrategyManual; break; // user game
    case 2  : playerStrategy = new StrategyRandom; break; // C-Life game RANDOM
    case 3  : playerStrategy = new StrategyOrdered; break; // C-Life game ORDERED
    default : throw std::runtime_error("Unknown game mode");
  }

  player->setStrategy( playerStrategy );
}

void Game::nextTurn(){
  ++turns_;

  if ( ::TURNS_MAX <= turns_ ){
    setInvalid();
  }
}

void Game::setInvalid() {
    isValid_ = false;
}

inline bool Game::isValid() const{
  return isValid_;
}

void Game::resetGame(){
  turns_ = 0;
  isValid_ = true;
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


 void Game::waitCertainKeyAsync(int32_t keycode){

      auto ch = ChoiceDevice::getInstanceAsync();
      if( ch == keycode)
        ChoiceDevice::getInstanceAsync(); // Block
 }