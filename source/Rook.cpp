// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.

#include "Rook.h"

bool Rook::move(  std::shared_ptr<Board> board,
                  const Player* player,
                  Piece*& piece,
                  const int32_t i,
                  const int32_t j,
                  int32_t& i2,
                  int32_t& j2,
                  bool& isKingUnderAttack ){

  if (      killForwardLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if ( killBackwardLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if ( killLeftLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if ( killRightLine( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if ( movePerpendicularLine( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else
    return false; // No more moves available. Pass next move to OPPONENT piece.
};
