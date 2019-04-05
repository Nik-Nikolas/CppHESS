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

  WinConsole( std::unique_ptr<std::mutex>& mainMutex ) : mainMutex_( mainMutex ){}

  void setFont( const int32_t font );

  void showBoard( const std::shared_ptr<Board> board ) const;

  void showPlayerData( const Player& player ) const;

  void controlKeyboard( std::shared_ptr<Board> board,
                        std::shared_ptr<Game> game );

  void delay();

  void clear();

  void start( std::shared_ptr<Board> board, std::shared_ptr<Game> game );

  std::unique_ptr<std::mutex>& getMutex(){
    return mainMutex_;
  }

private:
  std::unique_ptr<std::mutex>& mainMutex_;
};
#endif
