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

  // Pawn to be riborn.
  Piece *& metamorphosis = board->changeBoard()[i][j];

  // Find out pawn color.
  const PieceColor color = metamorphosis->getPieceColor();

  // Delete pawn.
  delete metamorphosis;

  // Create any light or heavy piece instead.
  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( (*rd)() );

  std::uniform_int_distribution<> dis( 0, 3 );
  const int32_t VAR = static_cast<int32_t>( dis( gen ) );

  switch( VAR ){
    default:
    case 0 :
      metamorphosis = new Queen( PieceCoordinates ( i, 'A' + j ), color );
      break;
    case 1 :
      metamorphosis = new Rook( PieceCoordinates ( i, 'A' + j ), color );
      break;
    case 2 :
      metamorphosis = new Bishop( PieceCoordinates ( i, 'A' + j ), color );
      break;
    case 3 :
      metamorphosis = new Knight( PieceCoordinates ( i, 'A' + j ), color );
      break;
  }
}



// Kill opponent pawn after long move.
bool Pawn::killOpponentPawnAfterLongMove( Board* board,
                                          const Player* player,
                                          Piece*& piece,
                                          const int32_t i,
                                          const int32_t j,
                                          int32_t& i2,
                                          int32_t& j2,
                                          bool& isKingUnderAttack ){

  // Long enemy move with enemy pawn killing isn't possible before 2 turn.
  if( board->getLastMovedPiece().lastMovedPieceTurn_ < 1 )
    return false;

  int32_t x = board->getLastMovedPiece().lastMovedPieceCoordinates_.x_;
  int32_t y = board->getLastMovedPiece().lastMovedPieceCoordinates_.y_;

  // Corner / border cases.
  assert( BoardGlobals::getSize() - 1 >= x &&
          0 <= x &&
          BoardGlobals::getSize() - 1 >= y &&
          0 <= y );

  Piece*& lastMovedPiece = board->changeBoard()[y][x];
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

                // Delete made last long move opponent pawn.
                delete lastMovedPiece;
                lastMovedPiece = nullptr;

                // Replace pawn diagonally to the certain square (forward and right/left).
                enemySquare = piece;
                enemySquare->markAsMoved();
                enemySquare->setPieceCoordinates( PieceCoordinates ( forward_y,
                                            'A' + x ) );
                i2 = forward_y;
                j2 = x;
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



bool Pawn::killLeftPawn ( Board* board,
                          const Player* player,
                          Piece*& piece,
                          const int32_t i,
                          const int32_t j,
                          int32_t& i2,
                          int32_t& j2,
                          bool& isKingUnderAttack ){

  int32_t pieceMaxYCoord = 0;
  int32_t step = 0;

  if( PieceColor::WHITE == piece->getPieceColor() &&
      BoardGlobals::getSize() - 1 > j &&
      BoardGlobals::getSize() - 1 > i ){
    step = 1;
    pieceMaxYCoord = BoardGlobals::getSize() - 1;
  }
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           0 < j &&
           0 < i ){
    step = -1;
    pieceMaxYCoord = 0;
  }
  else
    return false;

  int32_t leftEnemySquare_x = j + step;
  int32_t leftEnemySquare_y = i + step;

  Piece*& leftEnemySquare =
  board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x];

  if( leftEnemySquare &&
      leftEnemySquare->getPieceColor() != piece->getPieceColor() ){

    if( typeid( *leftEnemySquare ) == typeid( King ) )
      return false; // Let opponent King go.

    delete leftEnemySquare;
    leftEnemySquare = piece;
    leftEnemySquare->markAsMoved();
    leftEnemySquare->setPieceCoordinates( PieceCoordinates ( leftEnemySquare_y,
                                'A' + leftEnemySquare_x ) );
    i2 = leftEnemySquare_y;
    j2 = leftEnemySquare_x;
    // We cant use 'this' here because of its constness (rvalue).
    // Piece is a reference to pointer.
    piece = nullptr;


    // Save last move data: piece type and coordinates.
    board->cacheLastMovedPiece( leftEnemySquare->getPieceType(),
                                PieceCoordinates ( leftEnemySquare_y,
                                'A' + leftEnemySquare_x ),
                                leftEnemySquare->getPieceColor(),
                                player->getGame()->currentTurn() );

    // Pawn becomes new piece on the opposite board edge.
    if( pieceMaxYCoord == leftEnemySquare_y )
      pawnBecomesNewPiece( board,
                           leftEnemySquare_y,
                           leftEnemySquare_x );

    return true; // Pass next move to opponent.
  }

  return false;
}



bool Pawn::killRightPawn ( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           int32_t& i2,
                           int32_t& j2,
                           bool& isKingUnderAttack ){

  int32_t pieceMaxYCoord = 0;
  int32_t step = 0;

  if( PieceColor::WHITE == piece->getPieceColor() &&
      0 < j &&
      BoardGlobals::getSize() - 1 > i ){
    step = 1;
    pieceMaxYCoord = BoardGlobals::getSize() - 1;
  }
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           BoardGlobals::getSize() - 1 > j &&
           0 < i ){
    step = -1;
    pieceMaxYCoord = 0;
  }
  else
    return false;

  int32_t rightEnemySquare_y = i + step;
  int32_t rightEnemySquare_x = j - step;

  Piece*& rightEnemySquare =
  board->changeBoard()[rightEnemySquare_y][rightEnemySquare_x];

  if( rightEnemySquare &&
      rightEnemySquare->getPieceColor() != piece->getPieceColor() ){

    if( typeid( *rightEnemySquare ) == typeid( King ) )
      return false;

    delete rightEnemySquare;
    rightEnemySquare = piece;
    rightEnemySquare->markAsMoved();
    rightEnemySquare->setPieceCoordinates( PieceCoordinates ( rightEnemySquare_y,
                                'A' + rightEnemySquare_x ) );
    i2 = rightEnemySquare_y;
    j2 = rightEnemySquare_x;
    // We cant use 'this' here because of its constness (rvalue).
    // Piece is a reference to pointer.
    piece = nullptr;
    // Save last move data: piece type and coordinates.
    board->cacheLastMovedPiece( rightEnemySquare->getPieceType(),
                                PieceCoordinates ( rightEnemySquare_y,
                                'A' + rightEnemySquare_x ),
                                rightEnemySquare->getPieceColor(),
                                player->getGame()->currentTurn() );

    // Pawn becomes new piece on the opposite board edge.
    if( pieceMaxYCoord == rightEnemySquare_y )
      pawnBecomesNewPiece( board, rightEnemySquare_y, rightEnemySquare_x );

    return true; // Pass next move to opponent.
  }

  return false;
}



bool Pawn::movePawnForward ( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j,
                             int32_t& i2,
                             int32_t& j2,
                             const int32_t LONG_MOVE_STEP,
                             bool& isKingUnderAttack ){

  int32_t pieceMaxYCoord = 0;
  int32_t step = 0;

  if( PieceColor::WHITE == piece->getPieceColor() &&
      BoardGlobals::getSize() - 1 > i ){
    pieceMaxYCoord = BoardGlobals::getSize() - 1;
    step = 1;
  }
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           0 < i ){
    pieceMaxYCoord = 0;
    step = -1;
  }
  else
    return false;

  int32_t forwardSquare_y = i + step;

  // If in-front-square is empty - move forward.
  Piece*& forwardSquare = board->changeBoard()[forwardSquare_y][j];
  if( nullptr != forwardSquare )
    return false;

  // If pawn never moved before.
  bool isLongMove = false;
  if( false == piece->isEverMoved() ){

    // Pointer. Not a reference to pointer!
    Piece* temp = board->changeBoard()[forwardSquare_y][j];
    while ( nullptr == temp ){

      // Forbide pawn long move over half board absolute length.
      if( PieceColor::WHITE == piece->getPieceColor() &&
          LONG_MOVE_STEP - 1 < forwardSquare_y ||
          PieceColor::BLACK == piece->getPieceColor() &&
          BoardGlobals::getSize() - LONG_MOVE_STEP > forwardSquare_y ){
        break;
      }

      // Safe step forward (no out of boarders).
      forwardSquare_y += step;
      isLongMove = true;

      temp = board->changeBoard()[forwardSquare_y][j];
    }

    // Because we previously stepped forward to check forward obstacles.
    if( isLongMove )
      forwardSquare_y -= step;
  }

  // forwardSquare_y could be increased up to
  // BoardGlobals::getSize()/2 for first movers here.
  Piece*& forwardSquare2 = board->changeBoard()[forwardSquare_y][j];
  if( !forwardSquare2 ){

    // Mark pawn as long moved if it has moved long move.
    piece->setAsMadeLongMove( isLongMove );

    forwardSquare2 = piece;
    assert( forwardSquare2 == piece );

    forwardSquare2->markAsMoved();
    forwardSquare2->setPieceCoordinates( PieceCoordinates ( forwardSquare_y,
                               'A' + j ) );
    i2 = forwardSquare_y;
    j2 = j;

    piece = nullptr;
    assert( forwardSquare2 != piece );

    // Save last move data: piece type and coordinates.
    board->cacheLastMovedPiece( forwardSquare2->getPieceType(),
                                PieceCoordinates ( forwardSquare_y,
                               'A' + j ),
                                forwardSquare2->getPieceColor(),
                                player->getGame()->currentTurn() );

    if( pieceMaxYCoord == forwardSquare_y )
      pawnBecomesNewPiece( board, forwardSquare_y, j );

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

  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( (*rd)() );

  std::uniform_int_distribution<> dis( 1, BoardGlobals::getLongMoveStep() );
  const int32_t MOVE = static_cast<int32_t>( dis( gen ) );

  if( killLeftPawn ( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else if( killRightPawn ( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else if( killOpponentPawnAfterLongMove( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
    return true;
  else if( movePawnForward( board, player, piece, i, j, i2, j2,
                            MOVE,
                            isKingUnderAttack ) )
    return true;
  else
    return false;
};



// Stub for future AI func.
bool Pawn::isLegalMove( Board* board,
                        const PieceCoordinates& finish ){
  ;
}
