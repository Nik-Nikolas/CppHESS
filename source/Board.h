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
    PieceType lastMovedPieceType_;
    PieceCoordinates lastMovedPieceCoordinates_;
    PieceColor lastMovedPieceColor_;
    int32_t lastMovedPieceTurn_;

    LastMovedPiece(){
      reset();
    }

    void reset(){
      lastMovedPieceType_ = PieceType::NOT_DEFINED;
      lastMovedPieceCoordinates_ = PieceCoordinates( -1, 'A' - 1 );
      lastMovedPieceColor_ = PieceColor::NOT_DEFINED;
      lastMovedPieceTurn_ = -1;
    }
  };

public:
  Board() : lastMovedPiece_() {
    resizeBoard();
  }

  void clearBoard(){

    LastMovedPiece();

     for( auto i = 0; i < board_.size(); ++i )
      for( auto j = 0; j <  board_[i].size(); ++j ){
        delete board_[i][j];
        board_[i][j] = nullptr;
      }
  }

  void resizeBoard(){

    board_.resize( BoardGlobals::getSize() );
    for( auto i = 0; i < BoardGlobals::getSize(); ++i )
      board_[i].resize( BoardGlobals::getSize() );

    //board_.shrink_to_fit();
    //for( auto i = 0; i < BoardGlobals::getSize(); ++i )
    //  board_[i].shrink_to_fit();
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

  const std::vector<std::vector<Piece*> >& readBoard() const{
    return board_;
  }

  std::vector<std::vector<Piece*> >& changeBoard() {
    return board_;
  }

private:
  LastMovedPiece lastMovedPiece_;

  std::vector<std::vector<Piece*> > board_;
};
#endif
