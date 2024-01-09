// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "StrategyOrdered.h"
#include "Player.h"

#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"

// Ordered behavior
bool StrategyOrdered::play( std::shared_ptr<Board> board_,                     
                           std::shared_ptr<Game> game,
                           const Player* player, int32_t& i,
                           int32_t& j, int32_t& i2, int32_t& j2 ) const{

  const int32_t BSIZE = BoardGlobals::getSize();
  bool isKingUnderAttack = false;

  for(    i = 0; i < BSIZE;  ++i ){
    for(  j = 0; j < BSIZE;  ++j ){
      Piece*&  currentSquarePiece = board_->modify()[i][j]; // Ref to pointer
      // If piece exists and player color corresponds to piece color.
      if( currentSquarePiece &&
          currentSquarePiece->getPieceColor() == player->getColor() ){

        bool isMoved = currentSquarePiece->move( board_,
                                                 player,
                                                 currentSquarePiece,
                                                 i,
                                                 j,
                                                 i2,
                                                 j2,
                                                 isKingUnderAttack );
        if( isMoved )
          return true; // Player moved successfully.
        else
          continue; // Pass move to next piece.
      }
    }
  }

  return false; // Player has no moves or pieces here.
}
