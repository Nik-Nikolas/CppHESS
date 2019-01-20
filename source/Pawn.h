// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESPAWN
#define CPPHESSCLASSESPAWN

#include "Queen.h"

//! \brief Class Pawn.
//!  Pawn piece.
class Pawn: public Piece {
public:
  Pawn( const Pawn& )              = delete;
  Pawn& operator = ( const Pawn& ) = delete;
  Pawn()                           = delete;
  Pawn( const PieceCoordinates& pcd,
        const PieceColor& pcl ): Piece( pcd, PieceType::PAWN, pcl ) {}
  ~Pawn() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j,
                      int32_t& i2,
                      int32_t& j2,
                      bool& isKingUnderAttack ) override final;

private:
  void pawnBecomesNewPiece( Board* board,
                            const int32_t i,
                            const int32_t j );

  bool killOpponentPawnAfterLongMove( Board* board,
                                      const Player* player,
                                      Piece*& piece,
                                      const int32_t i,
                                      const int32_t j,
                                      int32_t& i2,
                                      int32_t& j2,
                                      bool& isKingUnderAttack );

  bool killLeftPawn ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j,
                      int32_t& i2,
                      int32_t& j2,
                      bool& isKingUnderAttack );

  bool killRightPawn ( Board* board,
                       const Player* player,
                       Piece*& piece,
                       const int32_t i,
                       const int32_t j,
                       int32_t& i2,
                       int32_t& j2,
                       bool& isKingUnderAttack );

  bool movePawnForward ( Board* board,
                         const Player* player,
                         Piece*& piece,
                         const int32_t i,
                         const int32_t j,
                         int32_t& i2,
                         int32_t& j2,
                         const int32_t longMoveStep,
                         bool& isKingUnderAttack );
};
#endif
