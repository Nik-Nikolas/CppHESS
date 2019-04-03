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
  Game( Board* board,
        WinConsole*& winConsole,
        std::mutex*& mainMutex );

  ~Game();

  void start();

  void setStrategy( Player* player );

  void reset();

  void nextTurn();

  void setInvalid() noexcept;

  void checkValid();

  const int32_t currentTurn() const;

  void setTurn( const int32_t turns );

  void makeTurn( Player* const player1,
                 const Player* const player2,
                 const WinConsole* console,
                 Board& board );

  const bool isRunning() const;

  //!< Heads or tails game - who plays white.
  const PieceColor headsOrTailsColor();

  std::mutex*& getMutex(){
    return mainMutex_;
  }

private:
  Board* board_;
  const WinConsole* winConsole_;
  std::mutex*& mainMutex_;

  int32_t turns_   { 0 };
  bool    isValid_ { true };
};
#endif
