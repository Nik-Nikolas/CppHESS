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

  WinConsole( std::mutex*& mainMutex ) : mainMutex_( mainMutex ){}

  void setFont( const int32_t font );

  void showBoard( const Board& board ) const;

  void showPlayerData( const Player& player ) const;

  void controlKeyboard( Board& board,
                        Game& game );

  void delay();

  void clear();

  void start( Board& board, Game& game );

  std::mutex*& getMutex(){
    return mainMutex_;
  }

private:
  std::mutex*& mainMutex_;
};
#endif
