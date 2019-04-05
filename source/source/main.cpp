// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Board.h"
#include "Game.h"
#include "WinConsole.h"
#include "BoardGlobals.h"
#include "King.h"
#include "C++HESS.h"

// Encapsulated in class (as a private static) variables.
int32_t BoardGlobals::size_         = 0;
int32_t BoardGlobals::longMoveStep_ = 0;
int32_t BoardGlobals::delay_        = 0;
int32_t BoardGlobals::framesStep_   = START_FRAME;
bool    BoardGlobals::isGlyphMode_  = true;
int32_t King::counter_              = 0;

// Singletons class members.
std::random_device* RandomDevice::rd_ = nullptr;
std::mutex* MutexDevice::m_           = nullptr;

int main(){

  // Mutex singleton (use unique_ptr to exclude mutual ownership)
  std::unique_ptr<std::mutex> mainMutex( MutexDevice::getInstance() );

  // Primary objects (use shared_ptr to share ownership because we use copies
  // of pointers in objects)
  std::shared_ptr<Board> board( new Board );
  std::shared_ptr<WinConsole> winConsole ( new WinConsole( mainMutex ) );
  std::shared_ptr<Game> game ( new Game( board, winConsole, mainMutex ) );

  // Execution in separate detached thread (keyboard events)
  winConsole->start( board, game );

  // Multigame cycle
  // (new game maybe launched from main menu or when game is out of turns)
  while( true ){
    try{
      game->start();
    }
    catch( GameIsOver& g ){
      // Reset game status
      game->resetGame();
      // Destroy old game and create a new one
      game.reset( new Game( board, winConsole, mainMutex ) );
    }
    catch(...){
      throw;
    }
  }

  RandomDevice::deleteInstance();

  return 0;
}
