#include "C++HESS.h"
#include "Classes.h"

bool Piece::killPiece( Board* board,
                       Piece*& piece,
                       const int32_t i,
                       const int32_t j ){

  Piece*& enemySquare =
  board->changeBoard()[i][j];

  if( nullptr == enemySquare ){
    // Check for empty square.
    return false;
  }
  else if( enemySquare->getPieceColor() == piece->getPieceColor() ){
    // Check for proper (enemy) color.
    return false;
  }
  else if( typeid( *enemySquare ) == typeid( King ) ){
    // Enemy king is immortal.
    return false;
  }
  else{
    // Here we can delete enemy piece.
    delete enemySquare;
    enemySquare = piece;
    piece->markAsMoved();
    piece = nullptr;

    // Pass next move to opponent.
    return true;
  }
}



bool Piece::movePiece( Board* board,
                       Piece*& piece,
                       const int32_t i,
                       const int32_t j ){

  // If no coordinates were changed or square is busy - treat next piece.
  Piece*& boardSquare =
  board->changeBoard()[i][j];
  if( boardSquare ){
    return false;
  }
  else {
    // Move piece.
    boardSquare = piece;
    piece->markAsMoved();
    piece = nullptr;

    // Pass next move to opponent.
    return true;
  }
}



bool Piece::killForwardLine( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j ){

  // Kill forward enemy in the any forward enemy Square.
  bool foundForwardEnemy = false;
  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;
  if( piece->getPieceColor() == PieceColor::WHITE && i < HEIGHT - 1){ // WHITES.

    while( forwardEnemySquare_y < HEIGHT - 1 ){
      ++forwardEnemySquare_y;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece == white - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 ){

    while( forwardEnemySquare_y > 0 ){
      --forwardEnemySquare_y;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece - black - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  }

  if( foundForwardEnemy )
    if ( piece->killPiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::killBackwardLine( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j ){

  // Kill backward enemy in the any backward enemy Square.
  bool foundBackwardEnemy = false;
  int32_t backwardEnemySquare_x = j;
  int32_t backwardEnemySquare_y = i;
  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 1 ){ // BLACKS.

    while( backwardEnemySquare_y < HEIGHT - 1){
      ++backwardEnemySquare_y;

      Piece* potentialPiece =
      board->changeBoard()[backwardEnemySquare_y][backwardEnemySquare_x];
      // If nearest forward piece == same color - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundBackwardEnemy = true;
          break;
        }
      }
    }
  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && i > 0 ){

    while( backwardEnemySquare_y > 0 ){
      --backwardEnemySquare_y;

      Piece* potentialPiece =
      board->changeBoard()[backwardEnemySquare_y][backwardEnemySquare_x];
      // If nearest forward piece - same color - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundBackwardEnemy = true;
          break;
        }
      }
    }
  }

  if( foundBackwardEnemy )
    if ( piece->killPiece( board,
                           piece,
                           backwardEnemySquare_y,
                           backwardEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::killLeftLine( Board* board,
                          const Player* player,
                          Piece*& piece,
                          const int32_t i,
                          const int32_t j ){

  // Kill left enemy in the any left enemy Square.
  bool foundLeftEnemy = false;
  int32_t leftEnemySquare_x = j;
  int32_t leftEnemySquare_y = i;
  if( piece->getPieceColor() == PieceColor::WHITE &&
      j < WIDTH - 1 ){ // WHITES.

    while( leftEnemySquare_x < WIDTH - 1 ){
      ++leftEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x];
      // If nearest left piece == same color - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == this->getPieceColor() )
          return false;
        else{
          foundLeftEnemy = true;
          break;
        }
      }
    }
  }// BLACKS.

  else if( piece->getPieceColor() == PieceColor::BLACK && j > 0 ){
    while( leftEnemySquare_x > 0 ){
      --leftEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x];
      // If nearest left piece - same color - do nothing.
      if( potentialPiece ){
          if( potentialPiece->getPieceColor() == this->getPieceColor() )
            return false;
          else{
            foundLeftEnemy = true;
            break;
        }
      }
    }
  }

  if( foundLeftEnemy )
    if ( piece->killPiece( board, piece, leftEnemySquare_y, leftEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::killRightLine( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j ){

  // Kill right enemy in the any right enemy Square.
  bool foundRightEnemy = false;
  int32_t rightEnemySquare_x = j;
  int32_t rightEnemySquare_y = i;
  if( piece->getPieceColor() == PieceColor::BLACK && j < WIDTH - 1){ // BLACKS.

    while( rightEnemySquare_x < WIDTH - 1 ){
      ++rightEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[rightEnemySquare_y][rightEnemySquare_x];
      // If nearest right piece == same color - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundRightEnemy = true;
          break;
        }
      }
    }
  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && j > 0 ){

    while( rightEnemySquare_x > 0 ){
      --rightEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[rightEnemySquare_y][rightEnemySquare_x];
      // If nearest right piece - same color - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundRightEnemy = true;
          break;
        }
      }
    }
  }

  if( foundRightEnemy )
    if ( piece->killPiece( board, piece, rightEnemySquare_y, rightEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::moveForwardLine2( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j,
                              const int32_t LENGTH ){

  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;
  int32_t squareIter = 0;

  if( piece->getPieceColor() == PieceColor::WHITE && i < HEIGHT - 1 ){ // WHITES.

    while( forwardSquare_y < HEIGHT - 1 &&
           squareIter < LENGTH ){
      ++forwardSquare_y;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[forwardSquare_y][forwardSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare ){
        --forwardSquare_y;
        break;
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 ){

    while( forwardSquare_y > 0 &&
           squareIter < LENGTH ){
      --forwardSquare_y;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[forwardSquare_y][forwardSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare ){
        ++forwardSquare_y;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
    return true; // Pass next move to opponent.
  else
    return false; // If no coordinates were changed or square is busy by king - treat next piece.
}



bool Piece::moveBackwardLine2( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j,
                               const int32_t LENGTH ){

  int32_t backwardSquare_x = j;
  int32_t backwardSquare_y = i;
  int32_t squareIter = 0;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < HEIGHT - 1 ){ // BLACKS.


    while( backwardSquare_y < HEIGHT - 1 &&
           squareIter < LENGTH ){
      ++backwardSquare_y;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[backwardSquare_y][backwardSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare ){
        --backwardSquare_y;
        break;
      }
    }
  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && i > 0 ){

    while( backwardSquare_y > 0 &&
           squareIter < LENGTH ){
      --backwardSquare_y;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[backwardSquare_y][backwardSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare ){

        ++backwardSquare_y;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, backwardSquare_y, backwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}


bool Piece::moveLeftLine2( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           const int32_t LENGTH  ){

  int32_t leftSquare_x = j;
  int32_t leftSquare_y = i;
  int32_t squareIter = 0;

  if( piece->getPieceColor() == PieceColor::WHITE && j < WIDTH - 1 ){ // WHITES.

    while( leftSquare_x < WIDTH - 1 &&
           squareIter < LENGTH ){
      ++leftSquare_x;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[leftSquare_y][leftSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare){
        --leftSquare_x;
        break;
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && j > 0 ){

    while( leftSquare_x > 0  &&
           squareIter < LENGTH ){
      --leftSquare_x;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[leftSquare_y][leftSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare ){
        ++leftSquare_x;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, leftSquare_y, leftSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveRightLine2( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           const int32_t LENGTH ){

  int32_t leftSquare_x = j;
  int32_t leftSquare_y = i;
  int32_t squareIter = 0;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      j < WIDTH - 1 ){ // BLACKS.

    while( leftSquare_x < WIDTH - 1 &&
           squareIter < LENGTH ){
      ++leftSquare_x;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[leftSquare_y][leftSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare){
        --leftSquare_x;
        break;
      }
    }
  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && j > 0 ){

    while( leftSquare_x > 0  &&
           squareIter < LENGTH ){
      --leftSquare_x;
      ++squareIter;

      Piece* potentialSquare =
      board->changeBoard()[leftSquare_y][leftSquare_x];
      // If nearest Square is busy - break cycle.
      if( potentialSquare ){
        ++leftSquare_x;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, leftSquare_y, leftSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveForwardSquare( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j ){

  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE && i < HEIGHT - 1){ // WHITES.

    ++forwardSquare_y;

  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 ){

    --forwardSquare_y;

  }

  if ( piece->movePiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::killForwardSquare( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j ){

  int32_t forwardSquare_x = j;
  int32_t forwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE && i < HEIGHT - 1){ // WHITES.

    ++forwardSquare_y;

  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 ){

    --forwardSquare_y;

  }

  if ( piece->killPiece( board, piece, forwardSquare_y, forwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}

bool Piece::moveBackwardSquare( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j ){

  int32_t backwardSquare_x = j;
  int32_t backwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK && i < HEIGHT - 1){ // BLACKS.

    ++backwardSquare_y;

  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && i > 0 ){

    --backwardSquare_y;

  }

  if ( piece->movePiece( board, piece, backwardSquare_y, backwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}

bool Piece::killBackwardSquare( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j ){

  int32_t backwardSquare_x = j;
  int32_t backwardSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK && i < HEIGHT - 1){ // BLACKS.

    ++backwardSquare_y;

  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && i > 0 ){

    --backwardSquare_y;

  }

  if ( piece->killPiece( board, piece, backwardSquare_y, backwardSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveLeftSquare( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j ){

  int32_t leftSquare_x = j;
  int32_t leftSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE && j < WIDTH - 1){ // WHITES.

    ++leftSquare_x;

  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && j > 0 ){

    --leftSquare_x;

  }

  if ( piece->movePiece( board, piece, leftSquare_y, leftSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::killLeftSquare( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j ){

  int32_t leftSquare_x = j;
  int32_t leftSquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE && j < WIDTH - 1){ // WHITES.

    ++leftSquare_x;

  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && j > 0 ){

    --leftSquare_x;

  }

  if ( piece->killPiece( board, piece, leftSquare_y, leftSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveRightSquare( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j ){

  int32_t leftSquare_x = j;
  int32_t leftSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      j < WIDTH - 1 ){ // BLACKS.

    ++leftSquare_x;

  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && j > 0 ){

    --leftSquare_x;

  }

  if ( piece->movePiece( board, piece, leftSquare_y, leftSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::killRightSquare( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j ){

  int32_t leftSquare_x = j;
  int32_t leftSquare_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      j < WIDTH - 1 ){ // BLACKS.

    ++leftSquare_x;

  }// WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE && j > 0 ){

    --leftSquare_x;

  }

  if ( piece->killPiece( board, piece, leftSquare_y, leftSquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::movePerpendicularSquare( Board* board,
                                     const Player* player,
                                     Piece*& piece,
                                     const int32_t i,
                                     const int32_t j ){

  const int32_t PERPENDICULAR_DIRECTIONS_MAX_AMT = 4;
  const int32_t MOVE = rand() % PERPENDICULAR_DIRECTIONS_MAX_AMT;
  const int32_t LENGTH = 1;

  if ( 0 == MOVE )
    if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  if ( 1 == MOVE )
    if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  if ( 2 == MOVE )
    if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  if ( 3 == MOVE )
    if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  return false; // No more moves available. Pass next move to OPPONENT piece.
}



bool Piece::movePerpendicularLine( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j ){

  const int32_t PERPENDICULAR_DIRECTIONS_MAX_AMT = 4;
  const int32_t MOVE = rand() % PERPENDICULAR_DIRECTIONS_MAX_AMT;
  const int32_t LENGTH = rand() % std::min( WIDTH, HEIGHT ) + 1;

  if ( 0 == MOVE )
    if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  if ( 1 == MOVE )
    if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  if ( 2 == MOVE )
    if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  if ( 3 == MOVE )
    if( moveLeftLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveForwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveRightLine2( board, player, piece, i, j , LENGTH ) )
      return true;
    else if( moveBackwardLine2( board, player, piece, i, j , LENGTH ) )
      return true;

  return false; // No more moves available. Pass next move to OPPONENT piece.
}



bool Piece::moveDiagonalSquare( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j ){

  const int32_t DIAGONAL_DIRECTIONS_MAX_AMT = 4;
  const int32_t MOVE = rand() % DIAGONAL_DIRECTIONS_MAX_AMT;
  const int32_t LENGTH = 1;

  if ( 0 == MOVE )
    if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;

  if ( 1 == MOVE )
    if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;

  if ( 2 == MOVE )
    if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;

  if ( 3 == MOVE )
    if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;

  return false; // No more moves available. Pass next move to OPPONENT piece.
}



bool Piece::moveDiagonalLine( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j ){

  const int32_t DIAGONAL_DIRECTIONS_MAX_AMT = 4;
  const int32_t MOVE = rand() % DIAGONAL_DIRECTIONS_MAX_AMT;
  const int32_t LENGTH = rand() % std::min( WIDTH, HEIGHT ) + 1;

  if ( 0 == MOVE )
    if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;

  if ( 1 == MOVE )
    if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;

  if ( 2 == MOVE )
    if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;

  if ( 3 == MOVE )
    if( moveDiagonalBackwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalForwardRightLine( board, player, piece, i, j, LENGTH ) )
      return true;
    else if( moveDiagonalBackwardLeftLine( board, player, piece, i, j, LENGTH ) )
      return true;

  return false; // No more moves available. Pass next move to OPPONENT piece.
}



bool Piece::killDiagonalForwardLeftLine( Board* board,
                                         const Player* player,
                                         Piece*& piece,
                                         const int32_t i,
                                         const int32_t j ){

  // Kill forward enemy in the any forward enemy Square.
  bool foundForwardEnemy = false;
  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j < WIDTH - 1 ){ // WHITES.

    while( forwardEnemySquare_y < HEIGHT - 1 &&
           forwardEnemySquare_x < WIDTH - 1){
      ++forwardEnemySquare_y;
      ++forwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece == white - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 && j > 0){

    while( forwardEnemySquare_y > 0 && forwardEnemySquare_x > 0){
      --forwardEnemySquare_y;
      --forwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece - black - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  }

  if( foundForwardEnemy )
    if ( piece->killPiece( board,
                           piece,
                           forwardEnemySquare_y,
                           forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::killDiagonalBackwardRightLine( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j ){

  // Kill backward enemy in the any backward enemy Square.
  bool foundBackwardEnemy = false;
  int32_t backwardEnemySquare_x = j;
  int32_t backwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE && i > 0 && j > 0 ){ // WHITES.

    while( backwardEnemySquare_y > 0 && backwardEnemySquare_x > 0 ){
      --backwardEnemySquare_y;
      --backwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[backwardEnemySquare_y][backwardEnemySquare_x];
      // If nearest backward piece == white - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundBackwardEnemy = true;
          break;
        }
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1 &&
           j < WIDTH - 1 ){

    while( backwardEnemySquare_y < HEIGHT - 1 &&
           backwardEnemySquare_x < WIDTH - 1 ){
      ++backwardEnemySquare_y;
      ++backwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[backwardEnemySquare_y][backwardEnemySquare_x];
      // If nearest backward piece - black - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundBackwardEnemy = true;
          break;
        }
      }
    }
  }

  if( foundBackwardEnemy )
    if ( piece->killPiece( board, piece, backwardEnemySquare_y, backwardEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::killDiagonalForwardRightLine( Board* board,
                                          const Player* player,
                                          Piece*& piece,
                                          const int32_t i,
                                          const int32_t j ){

  // Kill forward enemy in the any forward enemy Square.
  bool foundForwardEnemy = false;
  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j > 0 ){ // WHITES.

    while( forwardEnemySquare_y < HEIGHT - 1 &&
           forwardEnemySquare_x > 0 ){
      ++forwardEnemySquare_y;
      --forwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece == white - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 &&
           j < WIDTH - 1 ){

    while( forwardEnemySquare_y > 0 && forwardEnemySquare_x < WIDTH - 1 ){
      --forwardEnemySquare_y;
      ++forwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece - black - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  }

  if( foundForwardEnemy )
    if ( piece->killPiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}




bool Piece::killDiagonalBackwardLeftLine( Board* board,
                                          const Player* player,
                                          Piece*& piece,
                                          const int32_t i,
                                          const int32_t j ){

  // Kill forward enemy in the any forward enemy Square.
  bool foundForwardEnemy = false;
  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i > 0 &&
      j < WIDTH - 1 ){ // WHITES.

    while( forwardEnemySquare_y > 0 &&
           forwardEnemySquare_x < WIDTH - 1 ){
      --forwardEnemySquare_y;
      ++forwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece == white - exit.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::WHITE )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::BLACK ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i < HEIGHT - 1  &&
           j > 0  ){

    while( forwardEnemySquare_y < HEIGHT - 1 && forwardEnemySquare_x > 0){
      ++forwardEnemySquare_y;
      --forwardEnemySquare_x;

      Piece* potentialPiece =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest forward piece - black - do nothing.
      if( potentialPiece ){
        if( potentialPiece->getPieceColor() == PieceColor::BLACK )
          return false;

        if ( potentialPiece->getPieceColor() == PieceColor::WHITE ){
          foundForwardEnemy = true;
          break;
        }
      }
    }
  }

  if( foundForwardEnemy )
    if ( piece->killPiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.

  return false; // Square is the same / empty / busy by opposite king or same color piece - treat next piece.
}



bool Piece::moveDiagonalForwardLeftSquare( Board* board,
                                           const Player* player,
                                           Piece*& piece,
                                           const int32_t i,
                                           const int32_t j ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j < WIDTH - 1 ){ // WHITES.

    ++forwardEnemySquare_y;
    ++forwardEnemySquare_x;

  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 && j > 0){

    --forwardEnemySquare_y;
    --forwardEnemySquare_x;

  }

  if ( piece->movePiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}


bool Piece::killDiagonalForwardLeftSquare( Board* board,
                                           const Player* player,
                                           Piece*& piece,
                                           const int32_t i,
                                           const int32_t j ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j < WIDTH - 1 ){ // WHITES.

    ++forwardEnemySquare_y;
    ++forwardEnemySquare_x;

  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK && i > 0 && j > 0){

    --forwardEnemySquare_y;
    --forwardEnemySquare_x;

  }

  if ( piece->killPiece( board,
                         piece,
                         forwardEnemySquare_y,
                         forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalBackwardRightSquare( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j ){

  int32_t backwardEnemySquare_x = j;
  int32_t backwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE && i > 0 && j > 0 ){ // WHITES.

    --backwardEnemySquare_y;
    --backwardEnemySquare_x;

  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1 &&
           j < WIDTH - 1 ){

    ++backwardEnemySquare_y;
    ++backwardEnemySquare_x;

  }

  if ( piece->movePiece( board, piece, backwardEnemySquare_y, backwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::killDiagonalBackwardRightSquare( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j ){

  int32_t backwardEnemySquare_x = j;
  int32_t backwardEnemySquare_y = i;
  if( piece->getPieceColor() == PieceColor::WHITE && i > 0 && j > 0 ){ // WHITES.

    --backwardEnemySquare_y;
    --backwardEnemySquare_x;

  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1 &&
           j < WIDTH - 1 ){

    ++backwardEnemySquare_y;
    ++backwardEnemySquare_x;

  }

  if ( piece->killPiece( board, piece, backwardEnemySquare_y, backwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalForwardRightSquare( Board* board,
                                            const Player* player,
                                            Piece*& piece,
                                            const int32_t i,
                                            const int32_t j ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j > 0 ){ // WHITES.

    ++forwardEnemySquare_y;
    --forwardEnemySquare_x;

  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < WIDTH - 1 ){

    --forwardEnemySquare_y;
    ++forwardEnemySquare_x;

  }

  if ( piece->movePiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}


bool Piece::killDiagonalForwardRightSquare( Board* board,
                                            const Player* player,
                                            Piece*& piece,
                                            const int32_t i,
                                            const int32_t j ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j > 0 ){ // WHITES.

    ++forwardEnemySquare_y;
    --forwardEnemySquare_x;

  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < WIDTH - 1 ){

    --forwardEnemySquare_y;
    ++forwardEnemySquare_x;

  }

  if ( piece->killPiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalBackwardLeftSquare( Board* board,
                                            const Player* player,
                                            Piece*& piece,
                                            const int32_t i,
                                            const int32_t j ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i > 0 &&
      j < WIDTH - 1 ){ // WHITES.

      --forwardEnemySquare_y;
      ++forwardEnemySquare_x;

  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1  &&
           j > 0  ){

      ++forwardEnemySquare_y;
      --forwardEnemySquare_x;

  }

  if ( piece->movePiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}


bool Piece::killDiagonalBackwardLeftSquare( Board* board,
                                            const Player* player,
                                            Piece*& piece,
                                            const int32_t i,
                                            const int32_t j ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i > 0 &&
      j < WIDTH - 1 ){ // WHITES.

      --forwardEnemySquare_y;
      ++forwardEnemySquare_x;

  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1  &&
           j > 0  ){

      ++forwardEnemySquare_y;
      --forwardEnemySquare_x;

  }

  if ( piece->killPiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalForwardLeftLine( Board* board,
                                         const Player* player,
                                         Piece*& piece,
                                         const int32_t i,
                                         const int32_t j,
                                         const int32_t LENGTH ){

  int32_t forwardEnemySquare_x = j;
  int32_t forwardEnemySquare_y = i;
  int32_t lengthIter = 0;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j < WIDTH - 1 ){ // WHITES.

    while( forwardEnemySquare_y < HEIGHT - 1 &&
           forwardEnemySquare_x < WIDTH - 1 &&
           lengthIter < LENGTH ){
      ++forwardEnemySquare_y;
      ++forwardEnemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        --forwardEnemySquare_y;
        --forwardEnemySquare_x;
        break;
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j > 0){

    while( forwardEnemySquare_y > 0 &&
           forwardEnemySquare_x > 0 &&
           lengthIter < LENGTH ){
      --forwardEnemySquare_y;
      --forwardEnemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[forwardEnemySquare_y][forwardEnemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        ++forwardEnemySquare_y;
        ++forwardEnemySquare_x;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, forwardEnemySquare_y, forwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalBackwardRightLine( Board* board,
                                           const Player* player,
                                           Piece*& piece,
                                           const int32_t i,
                                           const int32_t j,
                                           const int32_t LENGTH ){

  int32_t backwardEnemySquare_x = j;
  int32_t backwardEnemySquare_y = i;
  int32_t lengthIter = 0;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i > 0 &&
      j > 0 ){ // WHITES.

    while( backwardEnemySquare_y > 0 &&
           backwardEnemySquare_x > 0 &&
           lengthIter < LENGTH ){
      --backwardEnemySquare_y;
      --backwardEnemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[backwardEnemySquare_y][backwardEnemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        ++backwardEnemySquare_y;
        ++backwardEnemySquare_x;
        break;
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1 &&
           j < WIDTH - 1 ){

    while( backwardEnemySquare_y < HEIGHT - 1 &&
           backwardEnemySquare_x < WIDTH - 1 &&
           lengthIter < LENGTH ){
      ++backwardEnemySquare_y;
      ++backwardEnemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[backwardEnemySquare_y][backwardEnemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        --backwardEnemySquare_y;
        --backwardEnemySquare_x;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, backwardEnemySquare_y, backwardEnemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalForwardRightLine( Board* board,
                                          const Player* player,
                                          Piece*& piece,
                                          const int32_t i,
                                          const int32_t j,
                                          const int32_t LENGTH ){

  int32_t enemySquare_x = j;
  int32_t enemySquare_y = i;
  int32_t lengthIter = 0;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 &&
      j > 0 ){ // WHITES.

    while( enemySquare_y < HEIGHT - 1 &&
           enemySquare_x > 0 &&
           lengthIter < LENGTH ){
      ++enemySquare_y;
      --enemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[enemySquare_y][enemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        --enemySquare_y;
        ++enemySquare_x;
        break;
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < WIDTH - 1 ){

    while( enemySquare_y > 0 &&
           enemySquare_x < WIDTH - 1 &&
           lengthIter < LENGTH ){
      --enemySquare_y;
      ++enemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[enemySquare_y][enemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        ++enemySquare_y;
        --enemySquare_x;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, enemySquare_y, enemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}



bool Piece::moveDiagonalBackwardLeftLine( Board* board,
                                          const Player* player,
                                          Piece*& piece,
                                          const int32_t i,
                                          const int32_t j,
                                          const int32_t LENGTH ){

  int32_t enemySquare_x = j;
  int32_t enemySquare_y = i;
  int32_t lengthIter = 0;

 if( piece->getPieceColor() == PieceColor::WHITE &&
      i > 0 &&
      j < WIDTH - 1 ){ // WHITES.

    while( enemySquare_y > 0 &&
           enemySquare_x < WIDTH - 1 &&
           lengthIter < LENGTH ){
      --enemySquare_y;
      ++enemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[enemySquare_y][enemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        ++enemySquare_y;
        --enemySquare_x;
        break;
      }
    }
  }// BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i < HEIGHT - 1  &&
           j > 0  ){

    while( enemySquare_y < HEIGHT - 1 &&
           enemySquare_x > 0 &&
           lengthIter < LENGTH ){
      ++enemySquare_y;
      --enemySquare_x;
      ++lengthIter;

      Piece* potentialSquare =
      board->changeBoard()[enemySquare_y][enemySquare_x];
      // If nearest square is busy - go to previous free pos. and break cycle.
      if( potentialSquare ){
        --enemySquare_y;
        ++enemySquare_x;
        break;
      }
    }
  }

  if ( piece->movePiece( board, piece, enemySquare_y, enemySquare_x ) )
      return true; // Pass next move to opponent.
  else
      return false; // If no coordinates were changed or square is busy - treat next piece.
}
