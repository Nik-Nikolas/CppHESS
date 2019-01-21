// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESPLAYER
#define CPPHESSCLASSESPLAYER

#include "Strategy.h"

//! \brief Class Player.
class Player: public Context{
public:
  Player( const std::string& name,
          Board* board,
          Game* game,
          const PieceColor& color );

  Player( const std::string& name,
          Board* board,
          Game* game,
          const Player& player );

  bool makeMove          ( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );
  bool makeRandomTestMove( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );
  bool makeManualMove    ( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );

  virtual bool useStrategy( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 )
  final {
    return operation_->use( board_, this, i, j, i2, j2 );
  }

  virtual void setStrategy( const Strategy* s ) noexcept final {
    operation_ = s;
  }

  const PieceColor& getColor() const noexcept{
    return color_;
  }

  const Game* getGame() const noexcept{
    return game_;
  }

  Game* changeGame() noexcept {
    return game_;
  }

  const std::string& getName() const noexcept{
    return name_;
  }

  void showData() const noexcept;

  void arrangePieces( const int32_t scenario );

private:
  void queensBattle ();
  void pawnsBattle ();
  void classicBattle ();
  void kingsDance();
  void bishopVsRook ();
  void bishopVsKnight();
  void bishopVsPawn ();
  void knightVsRook();
  void randomBattle();

  void setMyTurnPriority () noexcept;

  std::string name_;
  Board*      board_;
  Game*       game_;
  PieceColor  color_;
  bool        isMyTurn_ { false };
};
#endif
