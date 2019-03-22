// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Strategy.h"
#include "Player.h"

// Manual game behavior
bool Strategy1::play( Board*& board_, const Player* player, int32_t& i,
                     int32_t& j, int32_t& i2, int32_t& j2 ) const{

  const int32_t BSIZE = BoardGlobals::getSize();
  char j_ = '\0', j2_= '\0';
  char ch = '\0';
  char i_ = '\0', i2_ = '\0';
  bool isKingUnderAttack = false;

  std::cout << "\n  " << player->getColor() << "S turn:";

  while ( true ){

    while( _kbhit() )
      _getch();

    // To allow left game before each turn.
    std::cout << "\n  Press ANY KEY to proceed, ESC to exit to main menu: ";
    ch = _getch();
    if( 27 == ch )
      return false;

    // Read next turn coordinates.
    std::cout << "\n  Enter current-next piece coordinates, e.g. e2-e4: ";
    std::cin >> j_ >> i_ >> ch >> j2_ >> i2_;

    // Remove all characters from cin.
    std::cin.ignore( 100, '\n' );

    // Convert chars into 2D array coordinates.
    i  = i_  - 48          - 1;
    j  = 97  - j_  + BSIZE - 1;
    i2 = i2_ - 48          - 1;
    j2 = 97  - j2_ + BSIZE - 1;

    // Corner / border cases.
    if ( BSIZE <= j  ||
         BSIZE <= j2 ||
         BSIZE <= i  ||
         BSIZE <= i2 ||
         0 > j  ||
         0 > j2 ||
         0 > i  ||
         0 > i2 )
          continue;

    Piece*& currentSquarePiece = board_->modify()[i][j]; // Ref to pointer
    // If piece exists and player color corresponds to piece color.
    if( currentSquarePiece &&
        currentSquarePiece->getPieceColor() == player->getColor() ){

      bool isMoved = currentSquarePiece->movePiece( board_,
                                                    player,
                                                    currentSquarePiece,
                                                    i2,
                                                    j2 );
      if( isMoved )
        return true;
      else
        isMoved = currentSquarePiece->killPiece( board_,
                                                 player,
                                                 currentSquarePiece,
                                                 i2,
                                                 j2,
                                                 isKingUnderAttack );

      if( isMoved )
        return true; ; // Pass move to next piece.
    }
  }

  return false;
}



// Random moves behavior
bool Strategy2::play( Board*& board_, const Player* player, int32_t& i,
                     int32_t& j, int32_t& i2, int32_t& j2 ) const{

  bool isKingUnderAttack = false;
  const int32_t BSIZE = BoardGlobals::getSize();

  std::vector<std::pair<int32_t, int32_t> > vp;
  vp.reserve( BSIZE * BSIZE / 4 );

  PieceColor currentPlayerColor = player->getColor();

  // Find all pieces of player's color and put it to container.
  for(   auto i0 = 0; i0 < BSIZE; ++i0 )
    for( auto j0 = 0; j0 < BSIZE; ++j0 ){

      Piece*& currentSquarePiece = board_->modify()[i0][j0];

      if( currentSquarePiece &&
          currentSquarePiece->getPieceColor() == currentPlayerColor ){

        vp.push_back( std::pair<int32_t, int32_t>( i0, j0 ) );
      }
    }

  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( ( *rd )() );
  std::shuffle( vp.begin(), vp.end(), gen ); // Shuffle player pieces coordinates.

  for( auto& p: vp){

    i = p.first;
    j = p.second;

    Piece*& thisPiece = board_->modify()[i][j];

    assert( thisPiece != nullptr );

    if ( thisPiece->move( board_,
                          player,
                          thisPiece,
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



// Ordered behavior
bool Strategy3::play( Board*& board_, const Player* player, int32_t& i,
                     int32_t& j, int32_t& i2, int32_t& j2 ) const{

  const int32_t BSIZE = BoardGlobals::getSize();
  bool isKingUnderAttack = false;

  for(    i = 0; i < BSIZE;  ++i ){
    for(  j = 0; j < BSIZE;  ++j ){
      Piece*&  currentSquarePiece = board_->modify()[i][j]; // Ref to pointer
      // If piece exists and player color corresponds to piece color.
      if( currentSquarePiece &&
          currentSquarePiece->getPieceColor() == player->getColor() ){

        bool isMoved = currentSquarePiece->move( board_,
                                                 player,
                                                 currentSquarePiece,
                                                 i,
                                                 j,
                                                 i2,
                                                 j2,
                                                 isKingUnderAttack );
        if( isMoved )
          return true; // Player moved successfully.
        else
          continue; // Pass move to next piece.
      }
    }
  }

  return false; // Player has no moves or pieces here.
}
