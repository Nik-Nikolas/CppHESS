// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

//!< Comments style purpose: Doxygen.

// C++ 11,14:
// - lambdas >>> show( const std::vector<std::vector<Piece*> >& board )
// - std::crbegin/crend ( T ) >>> show( const std::vector<std::vector<Piece*> >& board )
// - nullPtr
// - apostrophe  1'000'000
// - enum class
// - fixed inreger int32_t
// - '= delete' for CTORs and ASOPs where necessary
// - '= default' for DTORs where necessary
// - 'override final' for virtual f of derived classes
// - auto for cycles counters
// - static_assert in main()
// - ...

// TODO:
// KING: teach king to hide from check or to surrender certain player if mate occurs.
// KING: check if lineBetween (king, rook) != lineUnderAttack while casting
// Pawn functions code refactoring.
// More AI for better play.

#ifndef CPPHESS
#define CPPHESS

#include <iostream>  // Basic IO
#include <iomanip>   // Console / IO / setw
#include <typeinfo>  // Types distinction check.

#include <vector>
#include <algorithm>

#include <ctime>     // rand(), srand() functionality.
#include <cmath>     // min()
#include <cassert>

#include <conio.h>   // Console / IO / _kbhit() AS dev.test functions.
#include <windows.h>

class Piece;
class Player;
class Board;
class Game;

static const int32_t START_DELAY    = 100;
static const int32_t TURNS_MAX      = 1'000'000;  // Typically it takes 50 turns
                                                  // for classic chess game.
static const int32_t START_BOARD_SIDE    = 8;
static const int32_t LATIN_ALPHABET_SIZE = 26;

enum class PieceColor : int32_t{ NOT_DEFINED = -1,
                                 BLACK,
                                 WHITE };



enum class PieceType : int32_t{ NOT_DEFINED = -1,
                                PAWN   = 1,
                                KNIGHT = 3,
                                BISHOP = 4,
                                ROOK   = 5,
                                QUEEN  = 9,
                                KING   = 0 };



//!< Console output TEMP CODE
enum ConsoleColor{              BLACK        = 0,
                                BLUE         = 1,
                                GREEN        = 2,
                                CYAN         = 3,
                                RED          = 4,
                                MAGENTA      = 5,
                                BROWN        = 6,
                                LIGHTGRAY    = 7,
                                DARKGRAY     = 8,
                                LIGHTBLUE    = 9,
                                LIGHTGREEN   = 10,
                                LIGHTCYAN    = 11,
                                LIGHTRED     = 12,
                                LIGHTMAGENTA = 13,
                                YELLOW       = 14,
                                WHITE        = 15 };



void SetColor(ConsoleColor text, ConsoleColor background); //!< Console output



//! \brief Overload << to print colors in console char mode style.
std::ostream& operator << ( std::ostream& s, const PieceColor& pt );



//! \brief Overload << to print pieces in console char mode style.
std::ostream& operator << ( std::ostream& s, const Piece* pt );



//! \brief Overload << to print pieces names in console char mode style.
std::ostream& operator << ( std::ostream& s, const PieceType& pt );



//! \brief Show current pieces on board set.
void show( const std::vector<std::vector<Piece*> >& board );
void delay();
void clear();



//! \brief PieceCoordinates class.
//!
//! Keeps two coordinates:
//! - y (vertical coordinate)
//! - x (horizontal coordinate)
struct PieceCoordinates{
  int32_t y_;
  int32_t x_;

  //!< - 65 to convert char to int coordinates.
  PieceCoordinates( int32_t y = 0, int32_t x = 65 ): y_( y ),
                                                     x_( x - 65 ) {} // 'A' = 65
};



//! \brief Exception class GameIsOver.
class GameIsOver{
};
#endif
