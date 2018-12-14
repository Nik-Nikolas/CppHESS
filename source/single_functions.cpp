// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Piece.h"
#include "C++HESS.h"

//! \brief Show board function.
//!
//! \param
//! \return
void show( const std::vector<std::vector<Piece*> >& board ) {

  int32_t line       = 0;
  bool isWhiteSquare = false;

  ConsoleColor currentBackColor  = ConsoleColor::WHITE;
  ConsoleColor currentPieceColor = ConsoleColor::WHITE;

  std::for_each( std::crbegin( board ), std::crend( board ), [&]( std::vector<Piece*> ivec ){
    std::for_each( std::crbegin( ivec ), std::crend( ivec ), [&]( Piece* piece ){
      if( isWhiteSquare ){
        SetColor( ConsoleColor::BLACK, ConsoleColor::DARKGRAY );
        currentBackColor = ConsoleColor::DARKGRAY;
      }
      else{
        SetColor( ConsoleColor::BLACK, ConsoleColor::LIGHTGRAY );
        currentBackColor = ConsoleColor::WHITE;
      }

      isWhiteSquare = isWhiteSquare == true ? false : true;
      if( piece ){

        currentPieceColor = piece->getPieceColor() ==
        PieceColor::WHITE ? ConsoleColor::WHITE : ConsoleColor::BLACK;

        if( ConsoleColor::DARKGRAY == currentBackColor ){
          SetColor( currentPieceColor, ConsoleColor::DARKGRAY );
        }
        else{
          SetColor( currentPieceColor, ConsoleColor::LIGHTGRAY );
        }

        std::cout << piece << " ";

      }
      else{
        std::cout << "  ";
      }
    });

    isWhiteSquare = true == isWhiteSquare ? false : true;

    SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );
    std::cout << "  " << std::setw(2) << std::setfill('0') << BoardGlobals::getSize() - line;
    ++line;
    std::cout << "\n";
  });

  SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );

  std::cout << "\n";
  for( auto k = 0; k < BoardGlobals::getSize(); ++k ){
    if( k < ::LATIN_ALPHABET_SIZE )
        std::cout << static_cast<char>( 'A' + k ) << " ";
    else
        std::cout << k + 1;
  }
  std::cout << "\n";
}



//! \brief BoardGlobals::getDelay() function.
//!
//! \param cycles Cycles amt
//! \return void
void delay(){

  std::cout << ". Delay = " << BoardGlobals::getDelay() << " ms.";

  Sleep( BoardGlobals::getDelay() );
}



//! \brief Windows CLS function.
void clear() {

    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo( console, &screen );

    FillConsoleOutputCharacterA( console,
                                 ' ',
                                 screen.dwSize.X * screen.dwSize.Y,
                                 topLeft,
                                 &written );
    FillConsoleOutputAttribute( console,
                                FOREGROUND_GREEN |
                                FOREGROUND_RED |
                                FOREGROUND_BLUE,
                                screen.dwSize.X * screen.dwSize.Y,
                                topLeft,
                                &written );

    SetConsoleCursorPosition( console, topLeft );
}



//! \brief Overload << to print colors in console char mode style.
std::ostream& operator << ( std::ostream& s, const PieceColor& pt ){

  std::string color;
  switch( pt ){
      case PieceColor::WHITE : color = "WHITE"; break;
      case PieceColor::BLACK : color = "BLACK"; break;
      default                : color = "?";
  }

  s << color;
  return s;
}



//! \brief Set console colors.
void SetColor( ConsoleColor text, ConsoleColor background ){

	HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

  SetConsoleTextAttribute( hStdOut, ( WORD )( ( background << 4 ) | text ) );
}



//! \brief Overload << to print pieces in console char mode style.
std::ostream& operator << ( std::ostream& s, const Piece* pt ){

  char ch = '\0';
  const PieceType TYPE = pt->getPieceType();

  switch( TYPE ){
      case PieceType::PAWN   : ch = '1'; break;
      case PieceType::KNIGHT : ch = '3'; break;
      case PieceType::BISHOP : ch = '4'; break;
      case PieceType::ROOK   : ch = '5'; break;
      case PieceType::QUEEN  : ch = '9'; break;
      case PieceType::KING   : ch =  5;  break;
      default                : ch = '?';
  }

  s << ch;

  return s;
}



//! \brief Overload << to print pieces names in console char mode style.
std::ostream& operator << ( std::ostream& s, const PieceType& pt ){

  std::string type;
  switch( pt ){
      case PieceType::PAWN   : type = "PAWN"; break;
      case PieceType::KNIGHT : type = "KNIGHT"; break;
      case PieceType::BISHOP : type = "BISHOP"; break;
      case PieceType::ROOK   : type = "ROOK"; break;
      case PieceType::QUEEN  : type = "QUEEN"; break;
      case PieceType::KING   : type = "KING";  break;
      default                : type = "?";
  }

  s << type;
  return s;
}
