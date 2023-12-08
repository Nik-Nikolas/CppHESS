// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"

#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"

Player::Player( const std::string& name,
                std::shared_ptr<Board> board,
                std::shared_ptr<Game> game,
                const PieceColor& color,
                std::mutex* mainMutex ) :
                                           name_ ( name ),
                                           board_( board ),
                                           game_ ( game ),
                                           color_( color ),
                                           mainMutex_( mainMutex ){
  setMyTurnPriority ();
}



Player::Player( const std::string& name,
                std::shared_ptr<Board> board,
                std::shared_ptr<Game> game,
                const Player& player,
                std::mutex* mainMutex ) :
                                        name_ ( name ),
                                        board_( board ),
                                        game_ ( game ),
                                        color_( player.getColor() ==
                                        PieceColor::WHITE ? PieceColor::BLACK :
                                                            PieceColor::WHITE ),
                                        mainMutex_( mainMutex ){
  setMyTurnPriority ();
}



void Player::showData() const noexcept{

  SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );

  int32_t x = BoardGlobals::getSize() - board_->getLastMovedPiece().lastMovedPieceCoordinates_.x_;

  std::cout <<
  "\n" <<
  name_ <<
  " (" <<
  color_ <<
  ") moved ";

  printPiece( board_->getLastMovedPiece().lastMovedPieceType_,
              PieceColor::WHITE );
  if( ::LATIN_ALPHABET_SIZE > x )
    std::cout << static_cast<char>( 'A' + x - 1 );
  else
    std::cout << x << ",";
  std::cout << board_->getLastMovedPiece().lastMovedPieceCoordinates_.y_ + 1 <<
  " Turn: " <<
  static_cast<int32_t>( game_->currentTurn() ) + 1;
  std::cout << " Frames: " << BoardGlobals::getFramesStep();
  std::cout <<"/";
  std::cout << BoardGlobals::getDelay() << " ms.";

  delay();
}



void Player::setMyTurnPriority() noexcept{

  isMyTurn_ = color_ == PieceColor::WHITE ? true : false;
}



void Player::queensBattle(){

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Queen* p = new Queen( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Queen* p = new Queen( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::bishopVsKnight(){

    for(  auto j = 0; j < BoardGlobals::getSize(); ++j )
    for(auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Knight* p = new Knight( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Bishop* p = new Bishop( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::kingsDance(){

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      King* p = new King( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      King* p = new King( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::pawnsBattle(){
/*
      Pawn* p = new Pawn( PieceCoordinates( 0, 'A' + 0 ), PieceColor::WHITE );
      board_->setPiece( p, 0, 0 );

      Pawn* p1 = new Pawn( PieceCoordinates( 0, 'A' + 2 ), PieceColor::WHITE );
      board_->setPiece( p1, 2, 0 );


      Pawn* p11 = new Pawn( PieceCoordinates( 0, 'A' + 4 ), PieceColor::WHITE );
      board_->setPiece( p11, 4, 0 );


      Pawn* p111 = new Pawn( PieceCoordinates( 0, 'A' + 6 ), PieceColor::WHITE );
      board_->setPiece( p111, 6, 0 );




      Pawn* p2 = new Pawn( PieceCoordinates( BoardGlobals::getSize() - 10 - 1, 'A' + 1 ), PieceColor::BLACK );
      board_->setPiece( p2, 1, BoardGlobals::getSize() - 10 - 1 );

      Pawn* p3 = new Pawn( PieceCoordinates( BoardGlobals::getSize() - 10 - 1, 'A' + 3 ), PieceColor::BLACK );
      board_->setPiece( p3, 3, BoardGlobals::getSize() - 10 - 1 );

      Pawn* p33 = new Pawn( PieceCoordinates( BoardGlobals::getSize() - 10 - 1, 'A' + 5 ), PieceColor::BLACK );
      board_->setPiece( p33, 5, BoardGlobals::getSize() - 10 - 1 );

      Pawn* p22 = new Pawn( PieceCoordinates( BoardGlobals::getSize() - 10 - 1, 'A' + 7 ), PieceColor::BLACK );
      board_->setPiece( p22, 7, BoardGlobals::getSize() - 10 - 1 );

    */


  for(  auto j = 0; j < BoardGlobals::getSize(); ++j )
    for(auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(  auto j = 0; j < BoardGlobals::getSize(); ++j )
    for(auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::knightVsRook(){

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Knight* p = new Knight( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Rook* p = new Rook( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::classicBattle(){

/*// TEST 0-0 and 0-0-0
  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 1; k < 2; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  King* k00 = new King( PieceCoordinates( 0, 'E' ), PieceColor::WHITE );
  board_->setPiece( k00, BoardGlobals::getSize() / 2 - 1, 0 );

  Rook* r10 = new Rook( PieceCoordinates( 0, 'A' ), PieceColor::WHITE );
  board_->setPiece( r10, 0, 0 );
  Rook* r200 = new Rook( PieceCoordinates( 0, 'H' ), PieceColor::WHITE );
  board_->setPiece( r200, BoardGlobals::getSize() - 1, 0 );


  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 1; k < 2; ++k ){
      Pawn* pb = new Pawn( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( pb, j, BoardGlobals::getSize() - k - 1 );
    }
  Rook* r1b0 = new Rook( PieceCoordinates( BoardGlobals::getSize() - 1, 'A' ), PieceColor::BLACK );
  board_->setPiece( r1b0, 0, BoardGlobals::getSize() - 1 );
  Rook* r2b0 = new Rook( PieceCoordinates( BoardGlobals::getSize() - 1, 'H' ), PieceColor::BLACK );
  board_->setPiece( r2b0, BoardGlobals::getSize() - 1, BoardGlobals::getSize() - 1 );

  King* k0b0 = new King( PieceCoordinates( BoardGlobals::getSize() - 1, 'E' ), PieceColor::BLACK );
  board_->setPiece( k0b0, BoardGlobals::getSize() / 2 - 1, BoardGlobals::getSize() - 1 );

return;

*/

  // WHITES
  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 1; k < 2; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  Knight* k1 = new Knight( PieceCoordinates( 0, 'B' ), PieceColor::WHITE );
  board_->setPiece( k1, 1, 0 );
  Knight* k2 = new Knight( PieceCoordinates( 0, 'G' ), PieceColor::WHITE );
  board_->setPiece( k2, BoardGlobals::getSize() - 2, 0 );

  Bishop* b1 = new Bishop( PieceCoordinates( 0, 'C' ), PieceColor::WHITE );
  board_->setPiece( b1, 2, 0 );
  Bishop* b2 = new Bishop( PieceCoordinates( 0, 'F' ), PieceColor::WHITE );
  board_->setPiece( b2, BoardGlobals::getSize() - 3, 0 );

  Rook* r1 = new Rook( PieceCoordinates( 0, 'A' ), PieceColor::WHITE );
  board_->setPiece( r1, 0, 0 );
  Rook* r2 = new Rook( PieceCoordinates( 0, 'H' ), PieceColor::WHITE );
  board_->setPiece( r2, BoardGlobals::getSize() - 1, 0 );

  // Letters - left to right! H G F E D C B A
  Queen* q = new Queen( PieceCoordinates( 0, 'E' ), PieceColor::WHITE);
  board_->setPiece( q, BoardGlobals::getSize() / 2, 0 );

  // Letters - left to right! H G F E D C B A
  King* k0 = new King( PieceCoordinates( 0, 'D' ), PieceColor::WHITE );
  board_->setPiece( k0, BoardGlobals::getSize() / 2 - 1, 0 );

  // BLACKS
  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 1; k < 2; ++k ){
      Pawn* pb = new Pawn( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( pb, j, BoardGlobals::getSize() - k - 1 );
    }

  Knight* k1b = new Knight( PieceCoordinates( BoardGlobals::getSize() - 1, 'B' ), PieceColor::BLACK );
  board_->setPiece( k1b, 1, BoardGlobals::getSize() - 1 );
  Knight* k2b = new Knight( PieceCoordinates( BoardGlobals::getSize() - 1, 'G' ), PieceColor::BLACK );
  board_->setPiece( k2b, BoardGlobals::getSize() - 2, BoardGlobals::getSize() - 1 );

  Bishop* b1b = new Bishop( PieceCoordinates( BoardGlobals::getSize() - 1, 'C' ), PieceColor::BLACK );
  board_->setPiece( b1b, 2, BoardGlobals::getSize() - 1 );
  Bishop* b2b = new Bishop( PieceCoordinates( BoardGlobals::getSize() - 1, 'F' ), PieceColor::BLACK );
  board_->setPiece( b2b, BoardGlobals::getSize() - 3, BoardGlobals::getSize() - 1 );

  Rook* r1b = new Rook( PieceCoordinates( BoardGlobals::getSize() - 1, 'A' ), PieceColor::BLACK );
  board_->setPiece( r1b, 0, BoardGlobals::getSize() - 1 );
  Rook* r2b = new Rook( PieceCoordinates( BoardGlobals::getSize() - 1, 'H' ), PieceColor::BLACK );
  board_->setPiece( r2b, BoardGlobals::getSize() - 1, BoardGlobals::getSize() - 1 );

  Queen* qb = new Queen( PieceCoordinates( BoardGlobals::getSize() - 1, 'E' ), PieceColor::BLACK);
  board_->setPiece( qb, BoardGlobals::getSize() / 2, BoardGlobals::getSize() - 1 );

  King* k0b = new King( PieceCoordinates( BoardGlobals::getSize() - 1, 'D' ), PieceColor::BLACK );
  board_->setPiece( k0b, BoardGlobals::getSize() / 2 - 1, BoardGlobals::getSize() - 1 );
}



void Player::bishopVsRook(){

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Rook* p = new Rook( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(  auto j = 0; j < BoardGlobals::getSize(); ++j )
    for(auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Bishop* p = new Bishop( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::bishopVsPawn(){

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Bishop* p = new Bishop( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::randomBattle(){

  std::random_device* rd = RandomDevice::getInstance(); // Singleton.
  std::mt19937 gen( (*rd)() );

  std::uniform_int_distribution<> dis( 0, 5 );

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Piece* p = nullptr;
      int32_t var = static_cast<int32_t>( dis( gen ) );
      switch( var ){

        case 0 :
          p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 1 :
          p = new Knight( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 2 :
          p = new Bishop( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 3 :
          p = new Rook( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 4 :
          p = new Queen( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 5 :
          if( 0 == King::getCounter() )
            p = new King( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          else
            p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );

          break;
      }

      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < BoardGlobals::getSize(); ++j )
    for( auto k = 0; k < BoardGlobals::getSize() / 4; ++k ){
      Piece* p = nullptr;
      int32_t var = static_cast<int32_t>( dis( gen ) );
      switch( var ){

        case 0 :
          p = new Pawn( PieceCoordinates( BoardGlobals::getSize() -
                                          k - 1, 'A' + j ),
                                          PieceColor::BLACK );
          break;
        case 1 :
          p = new Knight( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 2 :
          p = new Bishop( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 3 :
          p = new Rook( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 4 :
          p = new Queen( PieceCoordinates( BoardGlobals::getSize() - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 5 :
          if( 1 >= King::getCounter() )
            p = new King( PieceCoordinates( BoardGlobals::getSize() -
                                            k - 1, 'A' + j ),
                                            PieceColor::BLACK );
          else
            p = new Pawn( PieceCoordinates( BoardGlobals::getSize() -
                                k - 1, 'A' + j ),
                                PieceColor::BLACK );
          break;
      }

      board_->setPiece( p, j, BoardGlobals::getSize() - k - 1 );
    }
}



void Player::arrangePieces(){

  const int scenario = _getch() - 48;

  switch( scenario ){
    default:
    case 1 : classicBattle();
      break;
    case 2 : knightVsRook();
      break;
    case 3 : queensBattle();
      break;
    case 4 : pawnsBattle();
      break;
    case 5 : bishopVsPawn();
      break;
    case 6 : bishopVsKnight();
      break;
    case 7 : bishopVsRook();
      break;
    case 8 : randomBattle();
      break;
  }
}
