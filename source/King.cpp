// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"
#include "King.h"

bool King::move( Board* board,
                 const Player* player,
                 Piece*& piece,
                 const int32_t i,
                 const int32_t j,
                 int32_t& i2,
                 int32_t& j2,
                 bool& isKingUnderAttack ){

  if( makeCastling( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if( killForwardSquare( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if( killBackwardSquare( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if( killLeftSquare( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if( killRightSquare( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
     return true;
  else if( killDiagonalForwardLeftSquare( board, player,  piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killDiagonalBackwardRightSquare( board, player,  piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killDiagonalForwardRightSquare( board, player,  piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killDiagonalBackwardLeftSquare( board, player,  piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( movePerpendicularSquare( board, player,  piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else if( moveDiagonalSquare( board, player,  piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else
    return false; // No more moves available. Pass next move to OPPONENT piece.
}



bool King::makeCastling( Board* board,
                         const Player* player,
                         Piece*& piece,
                         const int32_t i,
                         const int32_t j,
                         int32_t& i2,
                         int32_t& j2,
                         bool& isKingUnderAttack ){

  int32_t rook_coord_x = 0;
  Piece*& king = piece; // Reference to a pointer.
  if ( findCastlingAvailiableRook( board, i, rook_coord_x ) )
    if ( checkEmptyHorizontalLine( board, i, j, rook_coord_x ) )
      if ( !king->isEverMoved() )
        if ( !king->isUnderAttack() )
        //!!!!!!!! if lineBetween(king, rook) == !lineUnderAttack
        // ADD THIS CHECK
        {
          // king is left (+1)/right(-1) to the rook.
          const int32_t SIGN = j < rook_coord_x ? 1 : -1;

          // Move king.
          movePiece( board, player, king, i, j + 2 * SIGN );
          i2 = i;
          j2 = j + 2 * SIGN;

          // Move rook.
          movePiece( board, player, board->changeBoard()[i][rook_coord_x], i, j + 1 * SIGN );

          // Decrease turns counter because 2 pieces moved simultaneously - this is one turn.
          Player* p = const_cast<Player*>(player); // Safe.
          p->changeGame()->setTurn( player->getGame()->currentTurn() - 1 );

          return  true;
        }

  return false; // No more moves available. Pass next move to OPPONENT piece.
}



// King looks for any available for castling rook.
// Rook: same horizontal line, never moved, same color.
bool King::findCastlingAvailiableRook( const Board* board,
                                       const int32_t king_coord_y,
                                       int32_t& rook_coord_x ){

  for( auto j = 0; j < BoardGlobals::getSize(); ++j ){

    Piece* currentSquarePiece = board->readBoard()[king_coord_y][j];

    if( currentSquarePiece &&
        currentSquarePiece->getPieceColor() == this->getPieceColor() &&
        currentSquarePiece->getPieceType() == PieceType::ROOK &&
        !currentSquarePiece->isEverMoved() ){

      rook_coord_x = j;

      return true;
    }
  }

  return false;
}



// Try to find any piece within (not including boarders) certain horizontal line.
bool King::checkEmptyHorizontalLine( const Board* board,
                                     const int32_t coord_y,
                                     const int32_t piece1_coord_x,
                                     const int32_t piece2_coord_x ){

    const int32_t START_X = std::min( piece1_coord_x, piece2_coord_x ) + 1;
    const int32_t STOP_X = std::max( piece1_coord_x, piece2_coord_x );

    Piece*  currentSquarePiece = nullptr;
    for( auto j = START_X; j < STOP_X; ++j ){

      currentSquarePiece = board->readBoard()[coord_y][j];

      if( currentSquarePiece )
        return false;
    }

    return true;
}



const int32_t King::getCounter() {

    return counter_;
}



void King::resetCounter() {

    counter_ = 0;
}



void King::increaseCounter() {

    ++counter_;
}
