// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESLASTMOVEDPIECE
#define CPPHESSCLASSESLASTMOVEDPIECE

#include "C++HESS.h"

//!< Last moved piece representation
struct LastMovedPiece{
  PieceType lastMovedPieceType_              { PieceType::NOT_DEFINED };
  PieceCoordinates lastMovedPieceCoordinates_{ PieceCoordinates( -1, 'A' - 1 ) };
  PieceColor lastMovedPieceColor_            { PieceColor::NOT_DEFINED };
  int32_t lastMovedPieceTurn_                { -1 };

  void reset(){
    lastMovedPieceType_ = PieceType::NOT_DEFINED;
    lastMovedPieceCoordinates_ = PieceCoordinates( -1, 'A' - 1 );
    lastMovedPieceColor_ = PieceColor::NOT_DEFINED;
    lastMovedPieceTurn_ = -1;
  }
};

#endif
