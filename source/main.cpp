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

// Encapsulated in class (as the private static) variables
int32_t BoardGlobals::size_         = 0;
int32_t BoardGlobals::longMoveStep_ = 0;
int32_t BoardGlobals::delay_        = 0;
int32_t BoardGlobals::framesStep_   = START_FRAME;
bool    BoardGlobals::isGlyphMode_  = true;
int32_t King::counter_              = 0;

// Singletons class members
std::random_device* RandomDevice::rd_ {};
std::mutex* MutexDevice::m_           {}; // Keyboard events semaphore
__CONIO_H* __CONIO_H_INST::conio_     {}; // Unix conio library impl
int32_t ChoiceDevice::choice_         {}; // Choice device
bool ChoiceDevice::isChoiceMade_      {};

int main(){

  // Create a factory to build the main game entities
  GameFactory factory;
  auto board = factory.makeBoard();
  auto console = factory.makeConsole( MutexDevice::getInstance() );
  console->setConsoleInputMode(ConsoleInputMode::SYNC);

  auto game = factory.makeGame( board, console, MutexDevice::getInstance() );

  // Keyboard events processing in a separate detached thread
  console->start( board, game );

  // Multiple game cycle
  while( true ){
    try{
      game->start();
    }
    catch(...){
      std::cerr << std::endl << "Unknown error occured." << std::endl;
      throw; 
    }

    game->resetGame();
  }

  return 0;
}
