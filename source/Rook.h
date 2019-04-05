// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESROOK
#define CPPHESSCLASSESROOK

#include "Bishop.h"

//! \brief Class Rook.
//!  Rook piece.
class Rook: public Piece {
public:
  Rook( const Rook& )              = delete;
  Rook& operator = ( const Rook& ) = delete;
  Rook( const PieceCoordinates& pcd,
        const PieceColor& pcl ): Piece( pcd, PieceType::ROOK, pcl ) {}
  ~Rook() = default;

  virtual bool move ( std::shared_ptr<Board> board,
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
