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

  Game* game = new Game();

  game->start();

  delete game;

  return 0;
}
