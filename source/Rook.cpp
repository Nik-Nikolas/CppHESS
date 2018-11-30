#include "C++HESS.h"
#include "Classes.h"

bool Rook::move(  Board* board,
                  const Player* player,
                  Piece*& piece,
                  const int32_t i,
                  const int32_t j ){

  if ( killForwardLine( board, player, piece, i, j ) )
     return true;
  else if ( killBackwardLine( board, player, piece, i, j ) )
     return true;
  else if ( killLeftLine( board, player, piece, i, j ) )
     return true;
  else if ( killRightLine( board, player, piece, i, j ) )
     return true;
  else if ( movePerpendicularLine( board, player, piece, i, j ) )
    return true;
  else
    return false; // No more moves available. Pass next move to OPPONENT piece.
};
