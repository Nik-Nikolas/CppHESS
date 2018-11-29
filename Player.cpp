#include "C++HESS.h"
#include "Classes.h"

Player::Player( const std::string& name,
                Board* board,
                Game* game,
                PieceColor color ) : name_ ( name ),
                                     board_( board ),
                                     game_ ( game ),
                                     color_( color ){
  setMyTurnPriority ();
}

Player::Player( const std::string& name,
                Board* board,
                Game* game,
                const Player& player ) : name_ ( name ),
                                         board_( board ),
                                         game_ ( game ),
                                         color_( player.getColor() ==
                                         PieceColor::WHITE ? PieceColor::BLACK :
                                                            PieceColor::WHITE ){
  setMyTurnPriority ();
}



bool Player::makeMove(){

  for(   auto i = 0; i < HEIGHT; ++i ){
    for( auto j = 0; j < WIDTH;  ++j ){
      Piece*&  currentSquarePiece = board_->changeBoard()[i][j]; // Ref to pointer
      // If piece exists and player color corresponds to piece color.
      if( currentSquarePiece &&
          currentSquarePiece->getPieceColor() == this->getColor() ){

        bool isMoved = currentSquarePiece->move( board_,
                                                 this,
                                                 currentSquarePiece,
                                                 i,
                                                 j );
        if( isMoved ) {
          std::cout << "\nPlayer " << name_ <<" (" << color_ <<
          ") have moved with piece [" <<
          WIDTH - j << "," << i + 1 << "]. Turn: " <<
          static_cast<int32_t>( game_->currentTurn() ) + 1;

          ::delay();

          return true; // Player moved successfully.
        }
      }
      // Cycle continues if current square has no correspondent color piece
      // or current piece has no moves.
    }
  }

  return false; // Player has no moves or pieces here.
}



bool Player::makeRandomMove(){

  int32_t i = 0;
  int32_t j = 0;
  const int32_t MAX_TURNS = HEIGHT * WIDTH / 2;
  int32_t k = 0;

  while( true ){

    i = rand() % HEIGHT;
    j = rand() % WIDTH;

    Piece*&  currentSquare = board_->changeBoard()[i][j]; // Ref to pointer
      // If piece exists and player color corresponds to piece color.
      if( currentSquare &&
          currentSquare->getPieceColor() == this->getColor() ){

      Piece*& currentSquarePiece = currentSquare; // Ref to pointer
      bool isMoved = currentSquarePiece->move( board_,
                                               this,
                                               currentSquarePiece,
                                               i,
                                               j );
      if( isMoved ) {
        std::cout << "\nPlayer " << name_ <<" (" << color_ <<
        ") have moved with piece [" <<
        WIDTH - j << "," << i + 1 << "]. Turn: " <<
        static_cast<int32_t>( game_->currentTurn() ) + 1;

        ::delay();

        return true; // Player moved successfully.
      }
    }

    ++k;
    if ( MAX_TURNS == k ){
      std::cout << "\nPlayer " << name_ << " had no random moves for a "
      "reasonable time. Turn: " <<
      static_cast<int32_t>( game_->currentTurn() ) + 1 << "\n";

      return true; // No random moves for a reasonable time;
    }
  }
}



const PieceColor& Player::getColor() const {
  return color_;
}



void Player::showData() const {

  SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK);

  std::cout << "\nPlayer " << name_ <<
  " (" << color_ << ") is making move. Turn: " <<
  static_cast<int32_t>( game_->currentTurn() ) + 1;

  ::delay();
}



void Player::setMyTurnPriority(){
  isMyTurn_ = color_ == PieceColor::WHITE ? true : false;
}



void Player::queensBattle(){
  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Queen* p = new Queen( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Queen* p = new Queen( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::bishopVsKnight(){
    for(  auto j = 0; j < WIDTH; ++j )
    for(auto k = 0; k < HEIGHT / 4; ++k ){
      Knight* p = new Knight( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Bishop* p = new Bishop( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::kingsDance(){
  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      King* p = new King( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      King* p = new King( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::pawnsBattle(){
  for(  auto j = 0; j < WIDTH; ++j )
    for(auto k = 0; k < HEIGHT / 4; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(  auto j = 0; j < WIDTH; ++j )
    for(auto k = 0; k < HEIGHT / 4; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::kingsBattle(){

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      King* p = new King( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Queen* p = new Queen( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::classicBattle(){

  // WHITES
  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 1; k < 2; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  Knight* k1 = new Knight( PieceCoordinates( 0, 'B' ), PieceColor::WHITE );
  board_->setPiece( k1, 1, 0 );
  Knight* k2 = new Knight( PieceCoordinates( 0, 'G' ), PieceColor::WHITE );
  board_->setPiece( k2, WIDTH - 2, 0 );

  Bishop* b1 = new Bishop( PieceCoordinates( 0, 'C' ), PieceColor::WHITE );
  board_->setPiece( b1, 2, 0 );
  Bishop* b2 = new Bishop( PieceCoordinates( 0, 'F' ), PieceColor::WHITE );
  board_->setPiece( b2, WIDTH - 3, 0 );

  Rook* r1 = new Rook( PieceCoordinates( 0, 'A' ), PieceColor::WHITE );
  board_->setPiece( r1, 0, 0 );
  Rook* r2 = new Rook( PieceCoordinates( 0, 'H' ), PieceColor::WHITE );
  board_->setPiece( r2, WIDTH - 1, 0 );

  Queen* q = new Queen( PieceCoordinates( 0, 'D' ), PieceColor::WHITE);
  board_->setPiece( q, WIDTH / 2, 0 );

  King* k0 = new King( PieceCoordinates( 0, 'E' ), PieceColor::WHITE );
  board_->setPiece( k0, WIDTH / 2 - 1, 0 );

  // BLACKS
  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 1; k < 2; ++k ){
      Pawn* pb = new Pawn( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( pb, j, HEIGHT - k - 1 );
    }

  Knight* k1b = new Knight( PieceCoordinates( HEIGHT - 1, 'B' ), PieceColor::BLACK );
  board_->setPiece( k1b, 1, HEIGHT - 1 );
  Knight* k2b = new Knight( PieceCoordinates( HEIGHT - 1, 'G' ), PieceColor::BLACK );
  board_->setPiece( k2b, WIDTH - 2, HEIGHT - 1 );

  Bishop* b1b = new Bishop( PieceCoordinates( HEIGHT - 1, 'C' ), PieceColor::BLACK );
  board_->setPiece( b1b, 2, HEIGHT - 1 );
  Bishop* b2b = new Bishop( PieceCoordinates( HEIGHT - 1, 'F' ), PieceColor::BLACK );
  board_->setPiece( b2b, WIDTH - 3, HEIGHT - 1 );

  Rook* r1b = new Rook( PieceCoordinates( HEIGHT - 1, 'A' ), PieceColor::BLACK );
  board_->setPiece( r1b, 0, HEIGHT - 1 );
  Rook* r2b = new Rook( PieceCoordinates( HEIGHT - 1, 'H' ), PieceColor::BLACK );
  board_->setPiece( r2b, WIDTH - 1, HEIGHT - 1 );

  Queen* qb = new Queen( PieceCoordinates( HEIGHT - 1, 'D' ), PieceColor::BLACK);
  board_->setPiece( qb, WIDTH / 2, HEIGHT - 1 );

  King* k0b = new King( PieceCoordinates( HEIGHT - 1, 'E' ), PieceColor::BLACK );
  board_->setPiece( k0b, WIDTH / 2 - 1, HEIGHT - 1 );
}



void Player::bishopVsRook(){
  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Rook* p = new Rook( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(  auto j = 0; j < WIDTH; ++j )
    for(auto k = 0; k < HEIGHT / 4; ++k ){
      Bishop* p = new Bishop( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::bishopVsPawn(){

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Pawn* p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 4; ++k ){
      Bishop* p = new Bishop( PieceCoordinates( WIDTH - k - 1, 'A' + j ), PieceColor::BLACK );
      board_->setPiece( p, j, WIDTH - k - 1 );
    }
}



void Player::randomBattle(){

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 2; ++k ){
      Piece* p;
      const int32_t PIECE = rand() % 6;
      switch( PIECE ){
        default :
        case 0 : p = new Pawn( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 1 : p = new Knight( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 2 : p = new Bishop( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 3 : p = new Rook( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 4 : p = new Queen( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
        case 5 : p = new King( PieceCoordinates( k, 'A' + j ), PieceColor::WHITE );
          break;
      }

      board_->setPiece( p, j, k );
    }

  for(   auto j = 0; j < WIDTH; ++j )
    for( auto k = 0; k < HEIGHT / 2; ++k ){
      Piece* p;
      const int32_t PIECE = rand() % 6;
      switch( PIECE ){
        default :
        case 0 : p = new Pawn( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 1 : p = new Knight( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 2 : p = new Bishop( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 3 : p = new Rook( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 4 : p = new Queen( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
        case 5 : p = new King( PieceCoordinates( HEIGHT - k - 1, 'A' + j ), PieceColor::BLACK );
          break;
      }

      board_->setPiece( p, j, HEIGHT - k - 1 );
    }
}



void Player::arrangePieces( const int32_t scenario ){
  switch( scenario ){
    default:
    case 1 : classicBattle();
      break;
    case 2 : kingsBattle();
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
