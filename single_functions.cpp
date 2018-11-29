#include "C++HESS.h"
#include "Classes.h"

//! \brief Show board function.
//!
//! \param
//! \return
void show( const std::vector<std::vector<Piece*> >& board ) {

  int32_t line       = 0;
  bool isWhiteSquare = false;

  ConsoleColor currentBackColor  = ConsoleColor::WHITE;
  ConsoleColor currentPieceColor = ConsoleColor::WHITE;

  std::for_each( board.rbegin(), board.rend(), [&]( std::vector<Piece*> ivec ){
      std::for_each( ivec.rbegin(), ivec.rend(), [&]( Piece* piece ){
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

          if( ConsoleColor::DARKGRAY == currentBackColor )
          {
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

      isWhiteSquare = isWhiteSquare == true ? false : true;

      SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );
      std::cout << "  " << std::setw(2) << std::setfill('0') << WIDTH - line;
      ++line;
      std::cout << "\n";
  });



SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );
  const int32_t LATIN_ALPHABET_LETTERS = 26;

  std::cout << "\n";
  for( auto k = 0; k < HEIGHT; ++k ){
    if( k < LATIN_ALPHABET_LETTERS )
        std::cout << static_cast<char>( 'A' + k ) << " ";
    else
        std::cout << k + 1;
  }
  std::cout << "\n";
}



//! \brief Delay function.
//!
//! \param cycles Cycles amt
//! \return void
void delay(){
  int32_t add = 0;
  char ch = '\0';

  static int32_t delay = 100;
  if( _kbhit() ){
    int32_t keyCode = _getch();

    if( keyCode == 61 ){
      if ( 0 == delay )
        delay = 100;
      else
        delay *= 2;
    }
    else if( keyCode == 45 )
      delay /= 2;
    else if( keyCode == 27 )
      exit( 0 );
    else if( keyCode == 32 ){
        std::cout << ". PAUSE MODE - PRINT ANY KEY TO PROCEED:";
        _getch();
    }
  }

  if ( delay < 0 )
    delay = 0;

  std::cout << ". Delay = " << delay << " ms.";

  Sleep( delay );
}



//! \brief Windows CLS function.
void clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
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
void SetColor( ConsoleColor text, ConsoleColor background )
{
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
  //s << ( pt->getPieceColor() == PieceColor::WHITE ? 'w' : 'b' );

  return s;
}
