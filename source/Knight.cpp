// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Knight.h"

bool Knight::move( Board* board,
                   const Player* player,
                   Piece*& piece,
                   const int32_t i,
                   const int32_t j,
                   int32_t& i2,
                   int32_t& j2,
                   bool& isKingUnderAttack ){

  if(      killForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;
  else if( killBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack  ) )
    return true;

  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( ( *rd )() );

  std::uniform_int_distribution<> dis( 0, 7 ); // give "true" 1/2 of the time
  const int32_t MOVE = static_cast<int32_t>( dis( gen ) );

/*
  void ( * moveFunc )( Board* board,
                  const Player* player,
                  Piece*& piece,
                  const int32_t i,
                  const int32_t j,
                  int32_t& i2,
                  int32_t& j2,
                  bool& isKingUnderAttack );

  std::vector<void* ( * )( void* )> v;
  v.push_back( ( void* ( * )( void* ) ) &moveForward2Right1 );
  v.push_back( ( void* ( * )( void* ) ) &moveForward1Right2 );
  v.push_back( ( void* ( * )( void* ) ) &moveForward2Left1 );
  v.push_back( ( void* ( * )( void* ) ) &moveForward1Left2 );
  v.push_back( ( void* ( * )( void* ) ) &moveBackward2Right1 );
  v.push_back( ( void* ( * )( void* ) ) &moveBackward1Right2 );
  v.push_back( ( void* ( * )( void* ) ) &moveBackward2Left1 );
  v.push_back( ( void* ( * )( void* ) ) &moveBackward1Left2 );

  std::shuffle( v.begin(), v.end(), gen ); // Shuffle coordinates.

  //std::vector<void *( * )( void * )::iterator vi;
  //for( std::cbegin(), std::cend(), ++vi );


   std::for_each( std::crbegin( v ), std::crend( v ), [&]( void* ( * moveFunc)( void* ) ){


                 if( ( * moveFunc )( board,
                  player,
                  piece,
                  i,
                  j,
                  i2,
                  j2,
                  isKingUnderAttack ) == true   ) return true;


                                                          } ){

      }


  switch ( MOVE ){
    default : // case 1 - default
    case 1  :
      moveFunc = moveForward2Right1;
      break;
    case 2  :
      moveFunc = moveForward1Right2;
      break;
    case 3  :
      moveFunc = moveForward2Left1;
      break;
    case 4  :
      moveFunc = moveForward1Left2;
      break;
    case 5  :
      moveFunc = moveBackward2Right1;
      break;
    case 6  :
      moveFunc = moveBackward1Right2;
      break;
    case 7  :
      moveFunc = moveBackward2Left1;
      break;
    case 8  :
      moveFunc = moveBackward1Left2;
      break;
  }
*/
  if ( 0 == MOVE ){
    if(      moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
  }
  else if( 1 == MOVE ){
    if(      moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
  }
  else if( 2 == MOVE ){
    if(      moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
  }
  else if( 3 == MOVE ){
    if(      moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
  }
  else if( 4 == MOVE ){
    if(      moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
  }
  else if( 5 == MOVE ){
    if(      moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
  }
  else if( 6 == MOVE ){
    if(      moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
  }
  else if( 7 == MOVE ){
    if(      moveBackward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
      return true;
    else if( moveForward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveForward1Left2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Right1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward1Right2( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
    else if( moveBackward2Left1( board, player, piece, i, j, i2, j2, isKingUnderAttack ) )
        return true;
  }

  return false; // No more moves available. Pass next move to OPPONENT piece.
}



bool Knight::moveForward2Right1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 int32_t i,
                                 int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 2 &&
      j > 0 ){ // WHITES.
    square_y += 2;
    square_x -= 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j < BoardGlobals::getSize() - 1 ){
    square_y -= 2;
    square_x += 1;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
};



bool Knight::killForward2Right1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 2 &&
      j > 0 ){ // WHITES.
    square_y += 2;
    square_x -= 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j < BoardGlobals::getSize() - 1 ){
    square_y -= 2;
    square_x += 1;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x, isKingUnderAttack ) ){

    // Coords of enemy piece.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveBackward2Left1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 2 &&
      j > 0 ){ // BLACKS.
    square_y += 2;
    square_x -= 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j < BoardGlobals::getSize() - 1 ){
    square_y -= 2;
    square_x += 1;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killBackward2Left1( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 2 &&
      j > 0 ){ // BLACKS.
    square_y += 2;
    square_x -= 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j < BoardGlobals::getSize() - 1 ){
    square_y -= 2;
    square_x += 1;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x, isKingUnderAttack ) ){

    // Coords of enemy piece.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveForward1Right2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 1 &&
      j > 1 ){ // WHITES.
    square_y += 1;
    square_x -= 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < BoardGlobals::getSize() - 2 ){
    square_y -= 1;
    square_x += 2;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killForward1Right2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 1 &&
      j > 1 ){ // WHITES.
    square_y += 1;
    square_x -= 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j < BoardGlobals::getSize() - 2 ){
    square_y -= 1;
    square_x += 2;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x,
                         isKingUnderAttack ) ){

    // Coords of enemy piece.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveBackward1Left2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 1 &&
      j > 1 ){ // BLACKS.
    square_y += 1;
    square_x -= 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j < BoardGlobals::getSize() - 2 ){
    square_y -= 1;
    square_x += 2;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killBackward1Left2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 1 &&
      j > 1 ){ // BLACKS.
    square_y += 1;
    square_x -= 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j < BoardGlobals::getSize() - 2 ){
    square_y -= 1;
    square_x += 2;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x,
                         isKingUnderAttack ) ){

    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveForward2Left1( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                int32_t& i2,
                                int32_t& j2,
                                bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 2 &&
      j < BoardGlobals::getSize() - 1 ){ // WHITES.
    square_y += 2;
    square_x += 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j > 0 ){
    square_y -= 2;
    square_x -= 1;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killForward2Left1( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j,
                               int32_t& i2,
                               int32_t& j2,
                               bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 2 &&
      j < BoardGlobals::getSize() - 1 ){ // WHITES.
    square_y += 2;
    square_x += 1;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 1 &&
           j > 0 ){
    square_y -= 2;
    square_x -= 1;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x,
                         isKingUnderAttack ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveBackward2Right1( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  int32_t& i2,
                                  int32_t& j2,
                                  bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 2 &&
      j < BoardGlobals::getSize() - 1 ){ // BLACKS.
    square_y += 2;
    square_x += 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j > 0 ){
    square_y -= 2;
    square_x -= 1;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killBackward2Right1( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j,
                                   int32_t& i2,
                                   int32_t& j2,
                                   bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 2 &&
      j < BoardGlobals::getSize() - 1 ){ // BLACKS.
    square_y += 2;
    square_x += 1;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 1 &&
           j > 0 ){
    square_y -= 2;
    square_x -= 1;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x,
                         isKingUnderAttack ) ){

    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveForward1Left2( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                int32_t& i2,
                                int32_t& j2,
                                bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 1 &&
      j < BoardGlobals::getSize() - 2 ){ // WHITES.
    square_y += 1;
    square_x += 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j > 1 ){
    square_y -= 1;
    square_x -= 2;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killForward1Left2( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::WHITE &&
      i < BoardGlobals::getSize() - 1 &&
      j < BoardGlobals::getSize() - 2 ){ // WHITES.
    square_y += 1;
    square_x += 2;
  } // BLACKS.
  else if( piece->getPieceColor() == PieceColor::BLACK &&
           i > 0 &&
           j > 1 ){
    square_y -= 1;
    square_x -= 2;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x,
                         isKingUnderAttack ) ){

    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::moveBackward1Right2( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  int32_t& i2,
                                  int32_t& j2,
                                  bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 1 &&
      j < BoardGlobals::getSize() - 2 ){ // BLACKS.
    square_y += 1;
    square_x += 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j > 1 ){
    square_y -= 1;
    square_x -= 2;
  }

  if ( piece->movePiece( board, player, piece, square_y, square_x ) ){

    // Coords of new piece square.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}



bool Knight::killBackward1Right2( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  int32_t& i2,
                                  int32_t& j2,
                                  bool& isKingUnderAttack ){
  int32_t square_x = j;
  int32_t square_y = i;

  if( piece->getPieceColor() == PieceColor::BLACK &&
      i < BoardGlobals::getSize() - 1 &&
      j < BoardGlobals::getSize() - 2 ){ // BLACKS.
    square_y += 1;
    square_x += 2;
  } // WHITES.
  else if( piece->getPieceColor() == PieceColor::WHITE &&
           i > 0 &&
           j > 1 ){
    square_y -= 1;
    square_x -= 2;
  }

  if ( piece->killPiece( board, player, piece, square_y, square_x,
                         isKingUnderAttack ) ){

    // Coords of enemy piece.
    i2 = square_y;
    j2 = square_x;

    return true; // Pass next move to opponent.
  }
  else
    return false; // If no coordinates were changed or Square is busy - treat next piece.
}
