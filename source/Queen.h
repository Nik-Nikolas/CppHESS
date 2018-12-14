// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESQUEEN
#define CPPHESSCLASSESQUEEN

#include "Piece.h"

//! \brief Class Queen.
//!  Queen piece.
class Queen: public Piece {
public:
  Queen( const Queen& )              = delete;
  Queen& operator = ( const Queen& ) = delete;
  Queen()                            = delete;
  Queen( const PieceCoordinates& pcd,
         const PieceColor& pcl ): Piece( pcd, PieceType::QUEEN, pcl ) {}
  ~Queen() = default;

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
