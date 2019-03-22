// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESWINCON
#define CPPHESSCLASSESWINCON

#include "BoardGlobals.h"

//! \brief Class WinConsole.
class WinConsole{
public:
  void setFont( const int32_t font );

  void showBoard( const Board& board );

  void showPlayerData( const Player& player );

  void controlKeyboard( Board& board,
                        Player& player,
                        Game& game,
                        WinConsole& console );

  void delay();

  void clear();
};
#endif
