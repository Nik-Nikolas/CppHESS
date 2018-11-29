#include "C++HESS.h"
#include "Classes.h"

bool Bishop::move( Board* board,
                   const Player* player,
                   Piece*& piece,
                   const int32_t i,
                   const int32_t j ){
  if( killDiagonalForwardLeftLine( board, player, piece, i, j ) )
    return true;
  else if( killDiagonalBackwardRightLine( board, player, piece, i, j ) )
    return true;
  else if( killDiagonalForwardRightLine( board, player, piece, i, j ) )
    return true;
  else if( killDiagonalBackwardLeftLine( board, player, piece, i, j ) )
    return true;
  else if( moveDiagonalLine( board, player, piece, i, j ) )
    return true;
  else
    return false; // No more moves available. Pass next move to OPPONENT piece.
};
