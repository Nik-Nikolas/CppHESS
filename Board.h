// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESBOARD
#define CPPHESSCLASSESBOARD

#include "Game.h"

//! \brief Class Board.
//!  Board keeps all pieces in its matrix-type container.
class Board{
  struct LastMovedPiece{
    PieceType lastMovedPieceType_              { PieceType::NOT_DEFINED };
    PieceCoordinates lastMovedPieceCoordinates_{ PieceCoordinates( -1, 'A' - 1 ) };
    PieceColor lastMovedPieceColor_            { PieceColor::NOT_DEFINED };
    int32_t lastMovedPieceTurn_                { -1 };

    void reset(){
      lastMovedPieceType_ = PieceType::NOT_DEFINED;
      lastMovedPieceCoordinates_ = PieceCoordinates( -1, 'A' - 1 );
      lastMovedPieceColor_ = PieceColor::NOT_DEFINED;
      lastMovedPieceTurn_ = -1;
    }
  };

public:
  Board() : lastMovedPiece_() {

    resize();
  }

  void clear(){

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

  void resize(){

    const int32_t B_SIZE = BoardGlobals::getSize();

    board_.resize( B_SIZE );
    for( auto i = 0; i < B_SIZE; ++i )
      board_[i].resize( B_SIZE );

    board_.shrink_to_fit();
    for( auto i = 0; i < B_SIZE; ++i )
      board_[i].shrink_to_fit();
  }

  void setPiece ( const Piece* p, const int32_t x, const int32_t y ){
    // To eliminate constness here is safe.
    board_ [y][x] = const_cast<Piece*>( p );
  }

  void cacheLastMovedPiece ( const PieceType& type,
                             const PieceCoordinates& coord,
                             const PieceColor& color,
                             const int32_t turn ){

    lastMovedPiece_.lastMovedPieceType_ = type;
    lastMovedPiece_.lastMovedPieceCoordinates_ = coord;
    lastMovedPiece_.lastMovedPieceColor_ = color;
    lastMovedPiece_.lastMovedPieceTurn_ = turn;
  }

  const LastMovedPiece& getLastMovedPiece() const{
    return lastMovedPiece_;
  }

  void resetLastMovedPiece(){
    lastMovedPiece_.reset();
  }

  const std::vector<std::vector<Piece*> >& read() const{
    return board_;
  }

  std::vector<std::vector<Piece*> >& modify() {
    return board_;
  }

private:
  LastMovedPiece lastMovedPiece_;

  std::vector<std::vector<Piece*> > board_;
};
#endif
