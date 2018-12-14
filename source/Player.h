// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESPLAYER
#define CPPHESSCLASSESPLAYER

#include "King.h"

//! \brief Class Player.
class Player{
public:
  Player( const std::string& name,
          Board* board,
          Game* game,
          const PieceColor& color );

  Player( const std::string& name,
          Board* board,
          Game* game,
          const Player& player );

  bool makeMove();
  bool makeRandomTestMove(); //!< EXPERIMENTAL

  void move( const PieceCoordinates& start,
             const PieceCoordinates& finish );

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
