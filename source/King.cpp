#include "C++HESS.h"
#include "Classes.h"

bool King::move( Board* board,
                 const Player* player,
                 Piece*& piece,
                 const int32_t i,
                 const int32_t j ){
  if( killForwardSquare( board, player, piece, i, j ) )
     return true;
  else if( killBackwardSquare( board, player, piece, i, j ) )
     return true;
  else if( killLeftSquare( board, player, piece, i, j ) )
     return true;
  else if( killRightSquare( board, player, piece, i, j ) )
     return true;
  else if( killDiagonalForwardLeftSquare( board, player,  piece, i, j ) )
    return true;
  else if( killDiagonalBackwardRightSquare( board, player,  piece, i, j ) )
    return true;
  else if( killDiagonalForwardRightSquare( board, player,  piece, i, j ) )
    return true;
  else if( killDiagonalBackwardLeftSquare( board, player,  piece, i, j ) )
    return true;
  else if( rand() % 2 && movePerpendicularSquare( board, player,  piece, i, j ) )
    return true;
  else if( moveDiagonalSquare( board, player,  piece, i, j ) )
    return true;
  else
    return false; // No more moves available. Pass next move to OPPONENT piece.
};
