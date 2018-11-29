#include "C++HESS.h"
#include "Classes.h"

bool Knight::move( Board* board,
                   const Player* player,
                   Piece*& piece,
                   const int32_t i,
                   const int32_t j ){
  if( killForward2Right1( board, player, piece, i, j ) )
    return true;
  else if( killForward1Right2( board, player, piece, i, j ) )
    return true;
  else if( killForward2Left1( board, player, piece, i, j ) )
    return true;
  else if( killForward1Left2( board, player, piece, i, j ) )
    return true;
  else if( killBackward2Right1( board, player, piece, i, j ) )
    return true;
  else if( killBackward1Right2( board, player, piece, i, j ) )
    return true;
  else if( killBackward2Left1( board, player, piece, i, j ) )
    return true;
  else if( killBackward1Left2( board, player, piece, i, j ) )
    return true;

  const int32_t KNIGHT_MOVES_MAX_AMT = 8;
  const int32_t MOVE = rand() % KNIGHT_MOVES_MAX_AMT;

  if ( 0 == MOVE ){
    if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
  }
  else if( 1 == MOVE ){
    if( moveForward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
  }
  else if( 2 == MOVE ){
    if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
      return true;
  }
  else if( 3 == MOVE ){
    if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
  }
  else if( 4 == MOVE ){
    if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
  }
  else if( 5 == MOVE ){
    if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
  }
  else if( 6 == MOVE ){
    if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
  }
  else if( 7 == MOVE ){
    if( moveBackward1Left2( board, player, piece, i, j ) )
      return true;
    else if( moveForward2Right1( board, player, piece, i, j ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j ) )
        return true;
  }

  return false; // No more moves available. Pass next move to OPPONENT piece.
};



bool Knight::moveForward2Right1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 int32_t i,
                                 int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 2 &&
      j > 0 ){ // WHITES.
    forwardSquare_y += 2;
    forwardSquare_x -= 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j < WIDTH - 1 ){
    forwardSquare_y -= 2;
    forwardSquare_x += 1;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killForward2Right1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 2 &&
      j > 0 ){ // WHITES.
    forwardSquare_y += 2;
    forwardSquare_x -= 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j < WIDTH - 1 ){
    forwardSquare_y -= 2;
    forwardSquare_x += 1;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveBackward2Left1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 2 &&
      j > 0 ){ // BLACKS.
    forwardSquare_y += 2;
    forwardSquare_x -= 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j < WIDTH - 1 ){
    forwardSquare_y -= 2;
    forwardSquare_x += 1;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killBackward2Left1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 2 &&
      j > 0 ){ // BLACKS.
    forwardSquare_y += 2;
    forwardSquare_x -= 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j < WIDTH - 1 ){
    forwardSquare_y -= 2;
    forwardSquare_x += 1;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveForward1Right2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j > 1 ){ // WHITES.
    forwardSquare_y += 1;
    forwardSquare_x -= 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < WIDTH - 2 ){
    forwardSquare_y -= 1;
    forwardSquare_x += 2;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killForward1Right2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j > 1 ){ // WHITES.
    forwardSquare_y += 1;
    forwardSquare_x -= 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < WIDTH - 2 ){
    forwardSquare_y -= 1;
    forwardSquare_x += 2;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveBackward1Left2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 1 &&
      j > 1 ){ // BLACKS.
    forwardSquare_y += 1;
    forwardSquare_x -= 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j < WIDTH - 2 ){
    forwardSquare_y -= 1;
    forwardSquare_x += 2;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killBackward1Left2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 1 &&
      j > 1 ){ // BLACKS.
    forwardSquare_y += 1;
    forwardSquare_x -= 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j < WIDTH - 2 ){
    forwardSquare_y -= 1;
    forwardSquare_x += 2;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveForward2Left1( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 2 &&
      j < WIDTH - 1 ){ // WHITES.
    forwardSquare_y += 2;
    forwardSquare_x += 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j > 0 ){
    forwardSquare_y -= 2;
    forwardSquare_x -= 1;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killForward2Left1( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 2 &&
      j < WIDTH - 1 ){ // WHITES.
    forwardSquare_y += 2;
    forwardSquare_x += 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j > 0 ){
    forwardSquare_y -= 2;
    forwardSquare_x -= 1;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveBackward2Right1( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 2 &&
      j < WIDTH - 1 ){ // BLACKS.
    forwardSquare_y += 2;
    forwardSquare_x += 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j > 0 ){
    forwardSquare_y -= 2;
    forwardSquare_x -= 1;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killBackward2Right1( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 2 &&
      j < WIDTH - 1 ){ // BLACKS.
    forwardSquare_y += 2;
    forwardSquare_x += 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j > 0 ){
    forwardSquare_y -= 2;
    forwardSquare_x -= 1;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveForward1Left2( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j < WIDTH - 2 ){ // WHITES.
    forwardSquare_y += 1;
    forwardSquare_x += 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j > 1 ){
    forwardSquare_y -= 1;
    forwardSquare_x -= 2;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killForward1Left2( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j < WIDTH - 2 ){ // WHITES.
    forwardSquare_y += 1;
    forwardSquare_x += 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j > 1 ){
    forwardSquare_y -= 1;
    forwardSquare_x -= 2;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::moveBackward1Right2( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 1 &&
      j < WIDTH - 2 ){ // BLACKS.
    forwardSquare_y += 1;
    forwardSquare_x += 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j > 1 ){
    forwardSquare_y -= 1;
    forwardSquare_x -= 2;
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killBackward1Right2( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j ){
  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 1 &&
      j < WIDTH - 2 ){ // BLACKS.
    forwardSquare_y += 1;
    forwardSquare_x += 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j > 1 ){
    forwardSquare_y -= 1;
    forwardSquare_x -= 2;
  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or Square is busy - treat next piece.
};
