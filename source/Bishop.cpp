// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Bishop.h"

bool Bishop::move( Board* board,
                   const Player* player,
                   Piece*& piece,
                   const int32_t i,
                   const int32_t j,
                   int32_t& i2,
                   int32_t& j2,
                   bool& isKingUnderAttack ){

  if(      killDiagonalForwardLeftLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killDiagonalBackwardRightLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killDiagonalForwardRightLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killDiagonalBackwardLeftLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( moveDiagonalLine( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else
    return false; // No more moves available. Pass next move to OPPONENT piece.
}
