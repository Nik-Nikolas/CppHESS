// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.

#include "Board.h"
#include "Game.h"
#include "Console.h"
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
__CONIO_H* __CONIO_H_INST::conio_     = nullptr;


int main(){

  // Create a factory to build the main game entities.
  GameFactory factory;
  auto board = factory.makeBoard();
  auto console = factory.makeConsole( MutexDevice::getInstance() );
  auto game = factory.makeGame( board, console, MutexDevice::getInstance() );

  // Keyboard events processing in a separate detached thread.
  console->start( board, game );

  // Multiple game cycle.
  while( true ){
    try{
      game->start();
    }
    catch( const GameIsOver& g ){
      // Reset the game
      game->resetGame();

      // Destroy the current game and create a new one instead.
      std::lock_guard<std::mutex> guard ( *game->getMutex() );
      game.reset( factory.makeGame( board, console, MutexDevice::getInstance() ).get() );
    }
    catch(...){
      std::cerr << std::endl << "Unknown error occured." << std::endl;
      throw; // Abort the game.
    }
  }

  return 0;
}
