// C++HESS.
// Igor Lobanov. 2017
//
// This is a header file.
//!< Comments style purpose: Doxygen.

// TODO:
// Teach king to hide from check or to surrender certain player if mate occurs.
// Teach pawn to kill opponent pawn after long move. Pawn functions code refactoring.
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

#include <conio.h>   // Console / IO / _kbhit() etc (yes- its bad - dev.test functions)
#include <windows.h>

static const int32_t WIDTH         = 40;     // Board width.
static const int32_t HEIGHT        = WIDTH;  // Board height.
static const int32_t TURNS_MAX     = 0xffff; // Typically it takes 50 turns
                                             // for classic chess game.
static const int32_t DELAY_CYCLES  = 0;



enum class PieceColor : int32_t{ BLACK, WHITE };



enum class PieceType : int32_t{ PAWN   = 1,
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



class Piece;
//! \brief Overload << to print pieces in console char mode style.
std::ostream& operator << ( std::ostream& s, const Piece* pt );
#endif
