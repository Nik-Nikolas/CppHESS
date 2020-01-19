// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESBOARD
#define CPPHESSCLASSESBOARD

#include "Game.h"
#include "LastMovedPiece.h"
#include "Piece.h"

//! \brief Class Board.
//!  Board keeps all pieces in its matrix-type container.
class Board{
public:
  Board();

  void clear();

  void resize();

  void setPiece ( const Piece* p, const int32_t x, const int32_t y );

  void cacheLastMovedPiece ( const PieceType& type,
                             const PieceCoordinates& coord,
                             const PieceColor& color,
                             const int32_t turn );

  const LastMovedPiece& getLastMovedPiece() const;

  void resetLastMovedPiece();

  const std::vector<std::vector<Piece*> >& read() const;

  std::vector<std::vector<Piece*> >& modify();

private:
  LastMovedPiece lastMovedPiece_;

  std::vector<std::vector<Piece*> > board_;
};
#endif
