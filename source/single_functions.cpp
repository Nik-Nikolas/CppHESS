// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Piece.h"
#include "C++HESS.h"
#include <cstdint>
#include<iostream>
#include <locale>
#include <cstring>


void printwc(wchar_t wc)
{
	char buf[2 * MB_CUR_MAX];

	mbstate_t state;
	memset(&state,0,sizeof(state));

	size_t offset1 = wcrtomb(buf, wc, &state);

	if(offset1 == size_t(-1))
	{
		std::cerr << "wcrtomb failed (1)" << std::endl;
		return;
	}

	size_t offset2 = wcrtomb(buf + offset1, L'\0', &state);

	if(offset2 == size_t(-1))
	{
		std::cerr << "wcrtomb failed (2)" << std::endl;
		return;
	}

	std::cout << buf;
}

void printPiece( const PieceType& PT,  const PieceColor& PC ){
#ifdef __linux__ 
  static wchar_t p;

  switch( PT ){
    case PieceType::PAWN   : PieceColor::WHITE == PC ? p = L'\u2659'  : p = L'\u265F' ; break;
    case PieceType::KNIGHT : PieceColor::WHITE == PC ? p = L'\u2658' : p = L'\u265E'; break;
    case PieceType::BISHOP : PieceColor::WHITE == PC ? p = L'\u2657' : p = L'\u265D'; break;
    case PieceType::ROOK   : PieceColor::WHITE == PC ? p = L'\u2656' : p = L'\u265C'; break;
    case PieceType::QUEEN  : PieceColor::WHITE == PC ? p = L'\u2655' : p = L'\u265B'; break;
    case PieceType::KING   : PieceColor::WHITE == PC ? p = L'\u2654' : p = L'\u265A'; break;
    default                : p = L'?'; break;
  }

	setlocale(LC_ALL, "");
	printwc(p);

#elif _WIN32

  static HANDLE cons = GetStdHandle( STD_OUTPUT_HANDLE );
  static const int BUFF_SIZE = 17;
  static wchar_t p[BUFF_SIZE];
  memset( p,'\0', BUFF_SIZE );
  static DWORD n;

  switch( PT ){
    case PieceType::PAWN   : PieceColor::WHITE == PC ? wcscpy (p, L"\u2659") : wcscpy (p, L"\u265F") ; break;
    case PieceType::KNIGHT : PieceColor::WHITE == PC ? wcscpy (p, L"\u2658") : wcscpy (p, L"\u265E"); break;
    case PieceType::BISHOP : PieceColor::WHITE == PC ? wcscpy (p, L"\u2657") : wcscpy (p, L"\u265D"); break;
    case PieceType::ROOK   : PieceColor::WHITE == PC ? wcscpy (p, L"\u2656") : wcscpy (p, L"\u265C"); break;
    case PieceType::QUEEN  : PieceColor::WHITE == PC ? wcscpy (p, L"\u2655") : wcscpy (p, L"\u265B"); break;
    case PieceType::KING   : PieceColor::WHITE == PC ? wcscpy (p, L"\u2654") : wcscpy (p, L"\u265A"); break;
    default                : wcscpy (p, L"?"); break;
  }

  WriteConsoleW( cons, p, wcslen( p ), &n, NULL );
#else
#endif
}


namespace Color {

    // "\033[{FORMAT_ATTRIBUTE};{FORGROUND_COLOR};{BACKGROUND_COLOR}m{TEXT}\033[{RESET_FORMATE_ATTRIBUTE}m"
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_GRAY     = 37,
        FG_DEFAULT  = 39,
        FG_WHITE    = 97,

        BG_BLACK    = 40,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_GRAY     = 47,
        BG_DEFAULT  = 49
    };

    class Modifier {
        Code fg;
        Code bg;
    public:
        Modifier(Code fg, Code bg) : fg(fg), bg(bg) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.fg << ';' << mod.bg << "m";
        }
    };
}


//! \brief Show board function.
//!
//! \param
//! \return
void show( const std::vector<std::vector<Piece*> >& board ) {
  std::cout << "\n";

  int32_t line       = 0;
  bool isWhiteSquare = false;

  static ConsoleColor currentBackColor;
  static ConsoleColor currentPieceColor;

  std::for_each( std::crbegin( board ), std::crend( board ), [&]( const auto& ivec ){
    std::for_each( std::crbegin( ivec ), std::crend( ivec ), [&]( const auto& piece ){
      if( isWhiteSquare ){
        SetColor( ConsoleColor::BLACK, ConsoleColor::LIGHTGRAY );
        currentBackColor = ConsoleColor::LIGHTGRAY;
      }
      else{
        SetColor( ConsoleColor::BLACK, ConsoleColor::GREEN );
        currentBackColor = ConsoleColor::GREEN;
      }

      isWhiteSquare = isWhiteSquare == true ? false : true;
      if( piece ){

        currentPieceColor = piece->getPieceColor() ==
        PieceColor::WHITE ? ConsoleColor::RED : ConsoleColor::BLUE;

        if( ConsoleColor::LIGHTGRAY == currentBackColor ){
          SetColor( currentPieceColor, ConsoleColor::LIGHTGRAY );
        }
        else{
          SetColor( currentPieceColor, ConsoleColor::GREEN );
        }

        if ( BoardGlobals::getGlyphMode() == true )
          printPiece( piece->getPieceType() ); // UTF-8 Glyph.
        else
          std::cout << piece; // Plain ASCII Text.

        std::cout << " ";

      }
      else{
        std::cout << "  ";
      }
    });

    isWhiteSquare = true == isWhiteSquare ? false : true;

    SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );
    std::cout << "" << std::setw( 2 ) << std::setfill( ' ' ) << BoardGlobals::getSize() - line;
    ++line;
    std::cout << "\n";
  });

  SetColor( ConsoleColor::WHITE, ConsoleColor::BLACK );

  //std::cout << "\n";
  const int32_t  BS = BoardGlobals::getSize();
  for( auto k = 0; k < BS; ++k ){
    if( ::LATIN_ALPHABET_SIZE > k )
        std::cout << static_cast<char>( 'A' + k ) << " ";
    else
        std::cout << k + 1;
  }
  std::cout << "\n";
}



//! \brief delay (sleep) due to game delay
//!
//! \return void
void delay(){
#ifdef __linux__ 
  std::this_thread::sleep_for(std::chrono::milliseconds(BoardGlobals::getDelay()));
#elif _WIN32
  Sleep( BoardGlobals::getDelay() );
#else
#endif
}

//! \brief delay for (sleep for) milliseconds
//!
//! \param milliseconds
//! \return void
void delay_for(std::uint32_t ms){
#ifdef __linux__ 
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#elif _WIN32
  Sleep( ms );
#else
#endif
}



//! \brief Windows CLS function.
void clearscr() {
#ifdef __linux__ 
    std::system ("clear");
#elif _WIN32

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
#else
#endif
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
#ifdef __linux__ 

    Color::Code fg;
    Color::Code bg;

    switch(text){
      case RED:         fg = Color::Code::FG_RED; break;
      case GREEN:       fg = Color::Code::FG_GREEN; break;
      case BLUE:        fg = Color::Code::FG_BLUE; break;
      case LIGHTGRAY:   fg = Color::Code::FG_GRAY; break;
      case WHITE:       fg = Color::Code::FG_WHITE; break;
      default:          fg = Color::Code::FG_GREEN;
    }

    switch(background){
      case RED:         bg = Color::Code::BG_RED; break;
      case GREEN:       bg = Color::Code::BG_GREEN; break;
      case BLUE:        bg = Color::Code::BG_BLUE; break;
      case LIGHTGRAY:   bg = Color::Code::BG_GRAY; break;
      case BLACK    :   bg = Color::Code::BG_BLACK; break;
      default:          bg = Color::Code::BG_GREEN;
    }

    std::cout << Color::Modifier(fg, bg);

#elif _WIN32
	HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  SetConsoleTextAttribute( hStdOut, ( WORD )( ( background << 4 ) | text ) );
#else
#endif
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
      case PieceType::KING   : ch = '0';  break;
      default                : ch = '?';
  }

  s << ch;
  return s;
}



//! \brief Overload << to print pieces names in console char mode style.
std::ostream& operator << ( std::ostream& s, const PieceType& PT ){

  std::string type;
  switch( PT ){
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