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
std::random_device*   RandomDevice::rd_ = nullptr;
std::mutex* MutexDevice::m_ = nullptr;

int main(){

  // Mutex singleton
  std::mutex* mutex = MutexDevice::getInstance();

  Board* board           = new Board;
  WinConsole* winConsole = new WinConsole( mutex );
  // Game needs board to change it and console to show board graphics
  Game* game             = new Game( board, winConsole, mutex );

  // Separate thread (second)
  winConsole->start( *board, *game);

  // Multigame cycle
  // (new game could be launched from main menu or when game is out of turns)
  while( true ){
    try{
      game->start();
    }
    catch( GameIsOver& g ){
      delete game;
      game = new Game( board, winConsole, mutex );
    }
    catch(...){
      throw;
    }
  }

  delete game;
  delete winConsole;
  delete board;
  MutexDevice::deleteInstance();

  return 0;
}
