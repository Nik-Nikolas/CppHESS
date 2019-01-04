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
  bool makeRandomTestMove( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 ); //!< EXPERIMENTAL
  bool makeManualMove    ( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );

  virtual bool useStrategy( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 ) final {
    return operation_->use( board_, this, i, j, i2, j2 );
  }

  virtual void setStrategy( Strategy* s ) final {
    operation_ = s;
  }

  const PieceColor& getColor() const;

  const Game* getGame() const{
    return game_;
  }

  Game* changeGame(){
    return game_;
  }

  const std::string& getName() const{
    return name_;
  }

  void showData() const;

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

  void setMyTurnPriority ();

  std::string name_;
  Board*      board_;
  Game*       game_;
  PieceColor  color_;
  bool        isMyTurn_;
};
#endif
