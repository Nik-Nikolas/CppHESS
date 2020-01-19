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

#include "GameFactory.h"

// Encapsulated in class (as the private static) variables.
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
  // Create a factory to build the main game entities.
  GameFactory factory;
  auto board = factory.makeBoard();
  auto winConsole = factory.makeConsole( MutexDevice::getInstance() );
  auto game = factory.makeGame( board, winConsole, MutexDevice::getInstance() );

  // Keyboard events processing a separate detached thread.
  winConsole->start( board, game );

  // Multiple game cycle.
  while( true ){
    try{
      game->start();
    }
    catch( const GameIsOver& g ){
      // Reset the game
      game->resetGame();

      // Destroy the current game and create a new one instead.
      game.reset( factory.makeGame( board, winConsole, MutexDevice::getInstance() ).get() );
    }
    catch(...){
      std::cerr << std::endl << "Unknown error occured." << std::endl;
      throw; // Abort the game.
    }
  }

  // Remove the mutex instance since it's not being used anymore.
  RandomDevice::deleteInstance();

  return 0;
}
