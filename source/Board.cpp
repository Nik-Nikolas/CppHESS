// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.

#include "LastMovedPiece.h"
#include "Board.h"

Board::Board() {

    // Set global settings
    BoardGlobals::setSize( ::START_BOARD_SIDE );
    BoardGlobals::setLongMoveStep( ::START_BOARD_SIDE / 2 );
    BoardGlobals::setDelay( ::START_DELAY );

    static_assert( ::START_BOARD_SIDE % 2 == 0,
                  "Board cells amount should be an even number.");

    resize();
  }

void Board::clear(){

  // struct CTOR . Clears all struct data.
  LastMovedPiece();

  const int32_t B_SIZE = board_.size();
  for( auto i = 0; i < B_SIZE; ++i ){

    const int32_t B_SIZE2 = board_[i].size();

    for( auto j = 0; j <  B_SIZE2; ++j ){

      delete board_[i][j];
      board_[i][j] = nullptr;
    }
  }
}

void Board::resize(){

  const int32_t B_SIZE = BoardGlobals::getSize();

  board_.resize( B_SIZE );
  for( auto i = 0; i < B_SIZE; ++i )
    board_[i].resize( B_SIZE );

  board_.shrink_to_fit();
  for( auto i = 0; i < B_SIZE; ++i )
    board_[i].shrink_to_fit();
}

void Board::setPiece ( const Piece* p, const int32_t x, const int32_t y ){
  // To eliminate constness here is safe.
  board_ [y][x] = const_cast<Piece*>( p );
}

void Board::cacheLastMovedPiece ( const PieceType& type,
                           const PieceCoordinates& coord,
                           const PieceColor& color,
                           const int32_t turn ){

  lastMovedPiece_.lastMovedPieceType_ = type;
  lastMovedPiece_.lastMovedPieceCoordinates_ = coord;
  lastMovedPiece_.lastMovedPieceColor_ = color;
  lastMovedPiece_.lastMovedPieceTurn_ = turn;
}

const LastMovedPiece& Board::getLastMovedPiece() const{
  return lastMovedPiece_;
}

void Board::resetLastMovedPiece(){
  lastMovedPiece_.reset();
}

const PieceMatrix& Board::read() const{
  return board_;
}

PieceMatrix& Board::modify() {
  return board_;
}
