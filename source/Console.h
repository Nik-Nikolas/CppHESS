// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESWINCON
#define CPPHESSCLASSESWINCON

#include "BoardGlobals.h"
#include "C++HESS.h"
#include <mutex>

enum class ConsoleInputMode {NOT_DEFINED, SYNC, SYNC_ECHO, ASYNC};

//! \brief Class Console.
class Console{
public:

  Console(  std::mutex* mainMutex ) : mainMutex_( mainMutex ){
  }

  void setFont( const int32_t font );

  void showBoard( const std::shared_ptr<Board> board ) const;

  void showPlayerData( const Player& player ) const;

  void controlKeyboard( std::shared_ptr<Board> board,
                        std::shared_ptr<Game> game );


  void delay();

  void clear();

  void start( std::shared_ptr<Board> board, std::shared_ptr<Game> game );

  std::mutex* getMutex(){
    return mainMutex_;
  }

  ConsoleInputMode getInputMode(){
    return mode_;
  }

  void setInputMode(ConsoleInputMode mode){
    std::lock_guard<std::mutex> l(*mainMutex_);
    mode_ = mode;
  }

private:
   std::mutex* mainMutex_;
   ConsoleInputMode mode_ {ConsoleInputMode::NOT_DEFINED};
};
#endif
