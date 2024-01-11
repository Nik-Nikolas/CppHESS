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

  void setInvalid();

  bool isValid() const;

  const int32_t currentTurn() const;

  void setTurn( const int32_t turns );

  bool makeTurn( Player* const player1,
                 const Player* const player2);

  //!< Heads or tails game - who plays white.
  const PieceColor headsOrTailsColor();

   std::mutex* getMutex(){
    return mainMutex_;
  }

  std::shared_ptr<Console> getConsole(){
    return console_;
  }

 void waitCertainKeyAsync(int32_t keycode);


private:
  std::shared_ptr<Board> board_;
  const std::shared_ptr<Console> console_;
  std::mutex* mainMutex_;

  int32_t turns_   { 0 };
  bool    isValid_ { true };
};
#endif
