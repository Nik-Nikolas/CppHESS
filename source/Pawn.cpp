// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"
#include "Pawn.h"

// Pawn becomes new piece on the opposite board edge.
void Pawn::pawnBecomesNewPiece( Board* board,
                                const int32_t i,
                                const int32_t j ){

          // Find out pawn color.
          PieceColor color = board->readBoard()[i][j]->getPieceColor();

          // Delete pawn.
          delete board->changeBoard()[i][j];

          // Create any other piece instead.
          board->changeBoard()[i][j] =
          new Queen( PieceCoordinates ( i, 'A' + j ), color );
}



// Kill opponent pawn after long move.
bool Pawn::killOpponentPawnAfterLongMove( Board* board,
                                          const Player* player,
                                          Piece*& piece,
                                          const int32_t i,
                                          const int32_t j  ){
  // Control border cases.
  //assert ( BoardGlobals::getSize() - 1 > j && 0 < j && BoardGlobals::getSize() - 1 > i && 0 < i );

  // Long enemy move with enemy pawn killing isn't possible before 2 turn.
  if( board->getLastMovedPiece().lastMovedPieceTurn_ < 1 )
    return false;

  int32_t x = board->getLastMovedPiece().lastMovedPieceCoordinates_.x_;
  int32_t y = board->getLastMovedPiece().lastMovedPieceCoordinates_.y_;


  assert( BoardGlobals::getSize() - 1 >= x &&
           0 <= x &&
           BoardGlobals::getSize() - 1 >= y &&
           0 <= y );

  Piece*& lastMovedPiece = board->changeBoard()[y][x];
  //std::cout<<player->getGame()->currentTurn();
  assert ( nullptr != lastMovedPiece );

  int32_t forward_y = 0;
  if( PieceColor::WHITE == piece->getPieceColor() ){
    forward_y = i + 1;
  }
  else{
    forward_y = i - 1;
  }

  Piece*& enemySquare = board->changeBoard()[forward_y][x];
  // Main conditions:
  // If potential square is empty for diagonal replacement (excessive condition?)
  // If x coord. is 1 square different.
  // If last moved piece is not the same color (impossible for classic chess).
  // If last moved piece is pawn.
  // If last moved pawn only moved once.
  // If last moved pawn made long move.

  // If last moved only once long moved different color pawn y coord <=
  // (or >= for BLACKS)
  // and x coord is 1 square different and its start coordinates have y
  // intersection and potential square is empty
  // - then kill opponent just long moved pawn and replace pawn diagonally
  // to a proper position.
  if( !enemySquare )
    if( j - 1 == x || j + 1 == x )
      if( board->getLastMovedPiece().lastMovedPieceColor_ != piece->getPieceColor() )
        if( board->getLastMovedPiece().lastMovedPieceType_ == PieceType::PAWN )
          if( true == lastMovedPiece->isMovedOnlyOnce() )
            if( true == lastMovedPiece->isMadeLongMove() )
              if( ( PieceColor::WHITE == piece->getPieceColor() &&
                    i >= y && // Black pawn long move square must be below or on the left/right position.
                    y - BoardGlobals::getLongMoveStep() > i ) || // Black pawn long move must intersect white pawn position.
                  ( PieceColor::BLACK == piece->getPieceColor() &&
                    i <= y && // White pawn long move square must be upper or on the left/right position.
                    y - BoardGlobals::getLongMoveStep()  < i ) ){ // White pawn long move must intersect black pawn position.

 // char ch = '\0';std::cout<<piece->getPieceColor() << " "<<(void*)lastMovedPiece << " " << (void*)enemySquare;  std::cin.get( ch );

                // Delete made last long move opponent pawn.
                delete lastMovedPiece;
                lastMovedPiece = nullptr;

                // Replace pawn diagonally to the certain square (forward and right/left).
                enemySquare = piece;
                piece->markAsMoved();
                piece = nullptr;

                // Save last move data: piece type and coordinates.
                board->cacheLastMovedPiece( enemySquare->getPieceType(),
                                            PieceCoordinates ( forward_y,
                                            'A' + x ),
                                            enemySquare->getPieceColor(),
                                            player->getGame()->currentTurn() );

                return true; // Pass next move to opponent.
              }

  return false;
}



bool Pawn::move( Board* board,
                 const Player* player,
                 Piece*& piece,
                 const int32_t i,
                 const int32_t j,
                 int32_t& i2,
                 int32_t& j2,
                 bool& isKingUnderAttack ){
  // WHITES.
  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 1 ){

    if( BoardGlobals::getSize() - 1 > j ){
      int32_t leftEnemySquare_x = j + 1;
      int32_t leftEnemySquare_y = i + 1;
      Piece*& leftEnemySquare =
      board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x];

      if( leftEnemySquare &&
          leftEnemySquare->getPieceColor() == PieceColor::BLACK ){

        if( typeid( *leftEnemySquare ) == typeid( King ) )
          return false;

        delete leftEnemySquare;
        leftEnemySquare = piece;
        piece->markAsMoved();
        // We cant use this here because of its constness (rvalue).
        // Piece is a reference to pointer.
        piece = nullptr;
        // Save last move data: piece type and coordinates.
        board->cacheLastMovedPiece( leftEnemySquare->getPieceType(),
                                    PieceCoordinates ( leftEnemySquare_y,
                                    'A' + leftEnemySquare_x ),
                                    leftEnemySquare->getPieceColor(),
                                    player->getGame()->currentTurn() );

        // Pawn becomes new piece on the opposite board edge.
        if( BoardGlobals::getSize() - 1 == leftEnemySquare_y )
          pawnBecomesNewPiece( board,
                               leftEnemySquare_y,
                               leftEnemySquare_x );

        return true; // Pass next move to opponent.
      }
    }

    // Kill right enemy in the right enemy Square.
    if( 0 < j ){
      int32_t rightEnemySquare_x = j - 1;
      int32_t rightEnemySquare_y = i + 1;
      Piece*& rightEnemySquare =
      board->changeBoard()[rightEnemySquare_y][rightEnemySquare_x];
      if( rightEnemySquare &&
          rightEnemySquare->getPieceColor() ==
          PieceColor::BLACK ){

        if( typeid( *rightEnemySquare ) == typeid( King ) )
          return false;

        delete rightEnemySquare;
        rightEnemySquare = piece;
        piece->markAsMoved();
        piece = nullptr;
        // Save last move data: piece type and coordinates.
        board->cacheLastMovedPiece( rightEnemySquare->getPieceType(),
                                    PieceCoordinates ( rightEnemySquare_y,
                                    'A' + rightEnemySquare_x ),
                                    rightEnemySquare->getPieceColor(),
                                    player->getGame()->currentTurn() );

        // Pawn becomes a new piece on the opposite board edge.
        if( BoardGlobals::getSize() - 1 == rightEnemySquare_y )
          pawnBecomesNewPiece( board,
                               rightEnemySquare_y,
                               rightEnemySquare_x );

        return true; // Pass next move to opponent.
      }
    }

    if( killOpponentPawnAfterLongMove( board, player, piece, i, j ) )
      return true; // Pass next move to opponent.

    // WHITES:If in-front-square is empty - move forward.
    int32_t forwardSquare_y = i + 1;
    Piece*& forwardSquare = board->changeBoard()[forwardSquare_y][j];
    if( nullptr != forwardSquare )
      return false; // No more moves available. Pass next move to next WHITE piece.

    // If pawn never moved before.
    bool isLongMove = false;
    if( false == piece->isEverMoved() ){

      // Pointer. Not a reference to pointer!
      Piece* temp = board->changeBoard()[forwardSquare_y][j];
      while ( nullptr == temp ){

      // Forbide pawn long move over half board absolute length.
      if( BoardGlobals::getLongMoveStep() - 1 < forwardSquare_y  )
        break;

        // Safe increment (no out of boarders).
        ++forwardSquare_y;
        isLongMove = true;

        temp = board->changeBoard()[forwardSquare_y][j];
      }

      // Because we previously ++ to check forward obstacles.
      if( isLongMove )
        --forwardSquare_y;
    }

    // forwardSquare_y could be increased up to BoardGlobals::getSize()/2 for first movers here.
    Piece*& forwardSquare2 =
    board->changeBoard()[forwardSquare_y][j];
    if( !forwardSquare2 ){

      // Mark pawn as long moved if it has moved long move.
      piece->setAsMadeLongMove( isLongMove );

      forwardSquare2 = piece;
      piece->markAsMoved();
      piece = nullptr;

      // Save last move data: piece type and coordinates.
      board->cacheLastMovedPiece( forwardSquare2->getPieceType(),
                                  PieceCoordinates ( forwardSquare_y,
                                 'A' + j ),
                                  forwardSquare2->getPieceColor(),
                                  player->getGame()->currentTurn() );

      if( BoardGlobals::getSize() - 1 == forwardSquare_y )
        pawnBecomesNewPiece( board,
                             forwardSquare_y,
                             j );

      return true; // Pass next move to opponent.
    }
  } // End of WHITE pawns tactics.
  else if ( piece->getPieceColor() == PieceColor::BLACK &&
            0 < i ) {
    // BLACKS: If pawn has any enemy piece to kill.
    // Kill left enemy.
    if( 0 < j ){
      int32_t leftEnemySquare_x = j - 1;
      int32_t leftEnemySquare_y = i - 1;
      Piece*& leftEnemySquare =
      board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x];
      if( leftEnemySquare &&
          leftEnemySquare->getPieceColor() ==
          PieceColor::WHITE ){

        if( typeid( *leftEnemySquare ) == typeid( King ) )
          return false;

        delete leftEnemySquare;
        leftEnemySquare = piece;
        piece->markAsMoved();
        piece = nullptr;
        // Save last move data: piece type and coordinates.
        board->cacheLastMovedPiece( leftEnemySquare->getPieceType(),
                                    PieceCoordinates ( leftEnemySquare_y,
                                    'A' + leftEnemySquare_x ),
                                    leftEnemySquare->getPieceColor(),
                                    player->getGame()->currentTurn() );

        if( 0 == leftEnemySquare_y )
          pawnBecomesNewPiece( board,
                               leftEnemySquare_y,
                               leftEnemySquare_x );

        return true; // Pass next move to opponent.
      }
    }

    // Kill right enemy.
    if( BoardGlobals::getSize() - 1 > j  ){
      int32_t rightEnemySquare_x = j + 1;
      int32_t rightEnemySquare_y = i - 1;
      Piece*& rightEnemySquare =
      board->changeBoard()[rightEnemySquare_y][rightEnemySquare_x];
      if( rightEnemySquare &&
          rightEnemySquare->getPieceColor() == PieceColor::WHITE ){

        if( typeid( *rightEnemySquare ) == typeid( King ) )
          return false;

        delete rightEnemySquare;
        rightEnemySquare = piece;
        piece->markAsMoved();
        piece = nullptr;

        // Save last move data: piece type and coordinates.
        board->cacheLastMovedPiece( rightEnemySquare->getPieceType(),
                                    PieceCoordinates ( rightEnemySquare_y,
                                    'A' + rightEnemySquare_x ),
                                    rightEnemySquare->getPieceColor(),
                                    player->getGame()->currentTurn() );

        // Pawn becomes Queen on the opposite board edge.
        if( 0 == rightEnemySquare_y )
          pawnBecomesNewPiece( board,
                               rightEnemySquare_y,
                               rightEnemySquare_x );

        return true; // Pass next move to opponent.
      }
    }

    // Kill opponent pawn after long move.
    if( killOpponentPawnAfterLongMove( board, player, piece, i, j ) )
      return true; // Pass next move to opponent.

    // BLACKS:If in-front-Square is empty - move forward.
    int32_t forwardSquare_y = i - 1;
    Piece*& forwardSquare = board->changeBoard()[forwardSquare_y][j];

    if( forwardSquare != nullptr )
      return false; // No more moves available. Pass next move to next BLACK piece.

    // If pawn never moved before.
    bool isLongMove = false;
    if( piece->isEverMoved() == false ){

      // Pointer. Not a reference to pointer!
      Piece* temp = board->changeBoard()[forwardSquare_y][j];
      while ( temp == nullptr ){

      // Forbide pawn long move over half board absolute length.
      if( forwardSquare_y < BoardGlobals::getLongMoveStep() )
        break;

        --forwardSquare_y;
        isLongMove = true;

        temp =  board->changeBoard()[forwardSquare_y][j];
      }

      // Because we previously ++ to check forward obstacles.
      if( isLongMove )
        ++forwardSquare_y;
    }

    // forwardSquare_y could be increased up to BoardGlobals::getSize()/2 for first movers here.
    Piece*& forwardSquare2 =
    board->changeBoard()[forwardSquare_y][j];
    if( !forwardSquare2 ){
      forwardSquare2 = piece;
      piece->markAsMoved();

      // Mark pawn as long moved if it has moved long move.
      piece->setAsMadeLongMove( isLongMove );

      // Save last move data: piece type and coordinates.
      board->cacheLastMovedPiece( forwardSquare2->getPieceType(),
                                  PieceCoordinates ( forwardSquare_y,
                                  'A' + j ),
                                  forwardSquare2->getPieceColor(),
                                  player->getGame()->currentTurn() );
      piece = nullptr;

      // Pawn becomes Queen on the opposite board edge.
      if( 0 == forwardSquare_y )
        pawnBecomesNewPiece( board,
                             forwardSquare_y,
                             j );

      return true; // Pass next move to opponent.
    }
  }

  return false; // No more moves available. Pass next move to OPPONENT piece.
};



// Stub for future AI func.
bool Pawn::isLegalMove( Board* board,
                        const PieceCoordinates& finish ){
  ;
}
