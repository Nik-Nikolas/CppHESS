// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESGAME
#define CPPHESSCLASSESGAME

#include "WinConsole.h"

//! \brief Class Game.
//!  Describes game process.
//!
//! Game validity state control:
//! - turns counter
//! - time control
class Game{
public:

  void startNewGame( Board& board, WinConsole& con );

  void reset(){
    turns_ = 0;
    isValid_ = true;
  }

  void nextTurn(){
    ++turns_;

    if (turns_ == ::TURNS_MAX)
      isValid_ = false;

    if (turns_ > ::TURNS_MAX)
      throw GameIsOver();
  }

  const bool isRunning() const {
    return isValid_;
  }

  const int32_t currentTurn() const{
    return turns_;
  }

  void setTurn( const int32_t turns ){
    turns_ = turns;
  }

  //!< Heads or tails game - who plays white.
  const PieceColor headsOrTailsColor(){

    std::random_device* rd = RandomDevice::getInstance(); // Singleton.
    std::mt19937 gen( ( *rd )() );
    // give "true" 1/2 of the time
    // give "false" 1/2 of the time
    std::bernoulli_distribution d( 0.5 );

    return d( gen ) ? PieceColor::WHITE : PieceColor::BLACK;
  }

private:
  int32_t turns_   { 0 };
  bool    isValid_ { true };
};
#endif
