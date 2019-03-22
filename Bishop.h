// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESBISHOP
#define CPPHESSCLASSESBISHOP

#include "Knight.h"

//! \brief Class Bishop.
//!  Bishop piece.
class Bishop: public Piece {
public:
  Bishop( const Bishop& )              = delete;
  Bishop& operator = ( const Bishop& ) = delete;
  Bishop()                             = delete;
  Bishop( const PieceCoordinates& pcd,
          const PieceColor& pcl ): Piece( pcd, PieceType::BISHOP, pcl ) {}
  ~Bishop() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j,
                      int32_t& i2,
                      int32_t& j2,
                      bool& isKingUnderAttack ) override final;
private:
};
#endif
