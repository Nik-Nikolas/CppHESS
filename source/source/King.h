// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESKING
#define CPPHESSCLASSESKING

#include "Rook.h"

//! \brief Class King.
//!  King piece.
class King: public Piece {
public:
  King( const King& )              = delete;
  King& operator = ( const King& ) = delete;
  King()                           = delete;
  King( const PieceCoordinates& pcd,
        const PieceColor& pcl ): Piece( pcd, PieceType::KING, pcl ) {
    increaseCounter();
  }
  ~King() { throw GameIsOver(); }; //!< Kings never die before the final.

  virtual bool move ( std::shared_ptr<Board> board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j,
                      int32_t& i2,
                      int32_t& j2,
                      bool& isKingUnderAttack ) override final;


  bool makeCastling( std::shared_ptr<Board> board,
                     const Player* player,
                     Piece*& piece,
                     const int32_t i,
                     const int32_t j,
                     int32_t& i2,
                     int32_t& j2,
                     bool& isKingUnderAttack );


  bool checkEmptyHorizontalLine( const std::shared_ptr<Board> board,
                                 const int32_t coord_y,
                                 const int32_t piece1_coord_x,
                                 const int32_t piece2_coord_x );

  bool findCastlingAvailiableRook( const std::shared_ptr<Board> board,
                                   const int32_t king_coord_x,
                                   int32_t& rook_coord_x );


  static const int32_t getCounter() {
    return counter_;
  }

  static void resetCounter() {
      counter_ = 0;
  }

private:
  static void increaseCounter() {
    ++counter_;
  }

  static int32_t counter_;
};
#endif
