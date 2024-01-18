// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "StrategyRandom.h"
#include "Player.h"

#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"

// Random moves behavior
bool StrategyRandom::play( std::shared_ptr<Board> board_,                     
                           std::shared_ptr<Game> game,
                           const Player* player, int32_t& i,
                           int32_t& j, int32_t& i2, int32_t& j2 ) const{

  bool isKingUnderAttack = false;
  const int32_t BSIZE = BoardGlobals::getSize();

  std::vector<Coords > vp;
  vp.reserve( BSIZE * BSIZE / 4 );

  PieceColor currentPlayerColor = player->getColor();

  // Find all pieces of player's color and put it to container.
  for(   auto i0 = 0; i0 < BSIZE; ++i0 )
    for( auto j0 = 0; j0 < BSIZE; ++j0 ){

      Piece*& currentSquarePiece = board_->modify()[i0][j0];

      if( currentSquarePiece &&
          currentSquarePiece->getPieceColor() == currentPlayerColor ){

        vp.push_back( Coords( i0, j0 ) );
      }
    }

  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( ( *rd )() );
  std::shuffle( vp.begin(), vp.end(), gen ); // Shuffle player pieces coordinates.

  for( auto& p: vp){

    i = p.first;
    j = p.second;

    Piece*& currentSquarePiece = board_->modify()[i][j];

    assert( currentSquarePiece != nullptr );

    if ( currentSquarePiece->move( board_,
                                   player,
                                   currentSquarePiece,
                                   i,
                                   j,
                                   i2,
                                   j2,
                                   isKingUnderAttack ) ){
      assert( i != i2 || j != j2 ); // Piece moved - coords have been changed.

      return true; // Player moved successfully.
    }
    else
      continue;
  }

  return false; // Player has no moves or pieces here.
}

