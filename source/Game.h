// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESGAME
#define CPPHESSCLASSESGAME

#include "Console.h"

//! \brief Class Game.
//!  Describes game process.
//!
//! Game validity state control:
//! - turns counter
//! - time control
class Game: public std::enable_shared_from_this<Game> {
public:
  Game( std::shared_ptr<Board> board,
        std::shared_ptr<Console> Console,
        std::mutex* mainMutex );

  ~Game(){
    RandomDevice::deleteInstance();
  };

  void start();

  void setStrategy( Player* player );

  void resetGame();

  void nextTurn();

  void setInvalid() noexcept;

  void checkValid();

  const int32_t currentTurn() const;

  void setTurn( const int32_t turns );

  void makeTurn( Player* const player1,
                 const Player* const player2,
                 const std::shared_ptr<Console> console,
                 std::shared_ptr<Board> board );

  const bool isRunning() const;

  //!< Heads or tails game - who plays white.
  const PieceColor headsOrTailsColor();

   std::mutex* getMutex(){
    return mainMutex_;
  }

private:
  std::shared_ptr<Board> board_;
  const std::shared_ptr<Console> Console_;
  std::mutex* mainMutex_;

  int32_t turns_   { 0 };
  bool    isValid_ { true };
};
#endif
