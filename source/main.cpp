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
int32_t BoardGlobals::size_        = 0;
int32_t BoardGlobals::longMoveStep_= 0;
int32_t BoardGlobals::delay_       = 0;
int32_t BoardGlobals::framesStep_  = START_FRAME;
bool    BoardGlobals::isGlyphMode_ = true;

int32_t King::counter_             = 0;

// Singleton class member.
std::random_device* RandomDevice::rd_ = nullptr;

int main(){

  BoardGlobals::setSize( ::START_BOARD_SIDE );
  BoardGlobals::setLongMoveStep( ::START_BOARD_SIDE / 2 );
  BoardGlobals::setDelay( ::START_DELAY );

  static_assert( ::START_BOARD_SIDE % 2 == 0,
                 "Board cells amount should be an even number.");

  Game* game = new Game();
  Board* board = new Board();
  WinConsole* console = new WinConsole();

  game->startNewGame( *board, *console );

  delete console;
  delete board;
  delete game;

  return 0;
}
