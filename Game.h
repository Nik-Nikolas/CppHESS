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
  Game();
  ~Game();

  void start();

  void setStrategy( Player* player );

  void reset();

  void nextTurn();

  const int32_t currentTurn() const;

  void setTurn( const int32_t turns );

  void makeTurn( Player* const player1,
                 const Player* const player2,
                 WinConsole& console,
                 Board& board );

  const bool isRunning() const;

  //!< Heads or tails game - who plays white.
  const PieceColor headsOrTailsColor();

private:
  Board* board_;
  WinConsole* winConsole_;

  int32_t turns_   { 0 };
  bool    isValid_ { true };
};
#endif
