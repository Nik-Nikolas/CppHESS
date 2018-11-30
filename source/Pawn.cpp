#include "C++HESS.h"
#include "Classes.h"

bool Pawn::move( Board* board,
                 const Player* player,
                 Piece*& piece,
                 const int32_t i,
                 const int32_t j ){
  // WHITES.
  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < HEIGHT - 1 ){

    // WHITES: If pawn has any enemy piece to kill.
    // Kill left enemy in the left enemy Square.
    if( j < WIDTH - 1 ){
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
        piece = nullptr;

        // Pawn becomes Queen on the opposite board edge.
        if( leftEnemySquare_y == HEIGHT - 1 ){
          delete board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x];
          board->changeBoard()[leftEnemySquare_y][leftEnemySquare_x] =
          new Queen( PieceCoordinates ( leftEnemySquare_y,
                                        'A' + leftEnemySquare_x ),
                                        PieceColor::WHITE );
        }

        return true; // Pass next move to opponent.
      }
    }

    // Kill right enemy in the right enemy Square.
    if( j > 0 ){
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

        // Pawn becomes Queen on the opposite board edge.
        if( rightEnemySquare_y == HEIGHT - 1 ){
          delete rightEnemySquare;
          rightEnemySquare =
          new Queen( PieceCoordinates ( rightEnemySquare_y,
                                        'A' + rightEnemySquare_x ),
                                        PieceColor::WHITE );
        }

        return true; // Pass next move to opponent.
      }
    }

    // TO DO - Kill right or left enemy pawn right after its' long move.
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // WHITES:If in-front-square is empty - move forward.
    int32_t forwardSquare_y = i + 1;
    Piece*& forwardSquare = board->changeBoard()[forwardSquare_y][j];
    if( forwardSquare != nullptr )
      return false; // No more moves available. Pass next move to next WHITE piece.

    // If pawn never moved before.
    if(  board->changeBoard()[i][j]->isEverMoved() == false  ){

      // Pointer. Not a reference to pointer!
      Piece* temp = board->changeBoard()[forwardSquare_y][j];
      bool isLongMove = false;
      while ( temp == nullptr ){

      // Forbide pawn long move over half board absolute length.
      if( forwardSquare_y > HEIGHT / 2 - 1 )
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

    // forwardSquare_y could be increased up to HEIGHT/2 for first movers here.
    Piece*& forwardSquare2 =
    board->changeBoard()[forwardSquare_y][j];
    if( !forwardSquare2 ){
      forwardSquare2 = piece;
      piece->markAsMoved();
      piece = nullptr;

      // Pawn becomes Queen on the opposite board edge.
      if( forwardSquare_y == HEIGHT - 1 ){
        delete forwardSquare2;
        forwardSquare2 =
        new Queen( PieceCoordinates ( forwardSquare_y,
                                      'A' + j ),
                                      PieceColor::WHITE );
      }

      return true; // Pass next move to opponent.
    }
  } // End of WHITE pawns tactics.
  else if ( piece->getPieceColor() == PieceColor::BLACK && i > 0 ) {
    // BLACKS: If pawn has any enemy piece to kill.
    // Kill left enemy.
    if( j > 0){
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

        // Pawn becomes Queen on the opposite board edge.
        if( leftEnemySquare_y == 0 ){
          delete leftEnemySquare;
          leftEnemySquare =
          new Queen( PieceCoordinates ( leftEnemySquare_y,
                                                      'A' + leftEnemySquare_x ),
                                                      PieceColor::BLACK );
        }

        return true; // Pass next move to opponent.
      }
    }

    // Kill right enemy.
    if( j < WIDTH - 1 ){
      int32_t rightEnemySquare_x = j + 1;
      int32_t rightEnemySquare_y = i - 1;
      Piece*& rightEnemySquare =
      board->changeBoard()[rightEnemySquare_y][rightEnemySquare_x];
      if( rightEnemySquare &&
          rightEnemySquare->getPieceColor() == PieceColor::WHITE ){

        if( typeid( *rightEnemySquare ) == typeid( King ) )
          return false;

        delete rightEnemySquare;
        rightEnemySquare =  piece;
        piece->markAsMoved();
        piece = nullptr;

        // Pawn becomes Queen on the opposite board edge.
        if( rightEnemySquare_y == 0 ){
          delete rightEnemySquare;
          rightEnemySquare =
          new Queen( PieceCoordinates ( rightEnemySquare_y,
                                                      'A' + rightEnemySquare_x ),
                                                      PieceColor::BLACK );
        }

        return true; // Pass next move to opponent.
      }
    }

    // BLACKS:If in-front-Square is empty - move forward.
    int32_t forwardSquare_y = i - 1;
    Piece*& forwardSquare = board->changeBoard()[forwardSquare_y][j];

    if( forwardSquare != nullptr )
      return false; // No more moves available. Pass next move to next BLACK piece.

    // If pawn never moved before.
    if( board->changeBoard()[i][j]->isEverMoved() == false ){

      // Pointer. Not a reference to pointer!
      Piece* temp = board->changeBoard()[forwardSquare_y][j];
      bool isLongMove = false;
      while ( temp == nullptr ){

      // Forbide pawn long move over half board absolute length.
      if( forwardSquare_y < HEIGHT / 2 )
        break;

        --forwardSquare_y;
        isLongMove = true;

        temp =  board->changeBoard()[forwardSquare_y][j];
      }

      // Because we previously ++ to check forward obstacles.
      if( isLongMove )
        ++forwardSquare_y;
    }

    // forwardSquare_y could be increased up to HEIGHT/2 for first movers here.
    Piece*& forwardSquare2 =
    board->changeBoard()[forwardSquare_y][j];
    if( !forwardSquare2 ){
      forwardSquare2 = piece;
      piece->markAsMoved();
      piece = nullptr;

      // Pawn becomes Queen on the opposite board edge.
      if( forwardSquare_y == 0 ){
        delete forwardSquare2;
        forwardSquare2 =
        new Queen( PieceCoordinates ( forwardSquare_y,
                                      'A' + j ),
                                      PieceColor::BLACK );
      }

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
