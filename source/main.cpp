// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Board.h"
#include "Game.h"
#include "WinConsole.h"
#include "BoardGlobals.h"
#include "C++HESS.h"

// Encapsulated in class (as a private static) variables
int32_t BoardGlobals::size_        = 0;
int32_t BoardGlobals::longMoveStep_= 0;
int32_t BoardGlobals::delay_       = 0;
int32_t BoardGlobals::framesStep_  = START_FRAME;
bool    BoardGlobals::isGlyphMode_ = true;

int main(){

  BoardGlobals::setSize( ::START_BOARD_SIDE );
  BoardGlobals::setLongMoveStep( ::START_BOARD_SIDE / 2 );
  BoardGlobals::setDelay( ::START_DELAY );

  static_assert( ::START_BOARD_SIDE % 2 == 0,
                 "Board cells amount should be an even number.");

  Game game;
  Board board;
  WinConsole console;

  game.startNewGame( board, console );

  return 0;
}
