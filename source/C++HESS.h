// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.
//
// Global constants, enums, structs, single functions, overloaded operators

//!< Comments style purpose: Doxygen.

// STL:
// - vector of vectors of pointers std::vector<std::vector<Piece*> >
// - for_each() with lambda functions for vector of vectors

// Design patterns:
// - SINGLETON ( std::random_device* )
// - STRATEGY for players behavior (instead of pointers to member functions)

// C++ 11,14:
// - lambdas >>> show( const std::vector<std::vector<Piece*> >& board )
// - std::crbegin/crend ( T )
//   >>> show( const std::vector<std::vector<Piece*> >& board )
// - nullPtr
// - apostrophe  1'000'000x
// - enum class uint8_t
// - fixed inreger int32_t
// - '= delete' for CTORs and ASOPs where necessary
// - '= default' for DTORs where necessary
// - '= override', '= final' for virtual f of derived classes
// - auto for cycles counters
// - static_assert in main()
// - uniform_int_distribution, bernoulli_distribution
// - void shuffle(RandomIt first, RandomIt last, URBG&& g)
// - for( auto& p: vp)
// - default values initialization for class members T t {val};
// - noexcept functions
// - multithreading:
//     - Detached threads with passed parameters
// - std::unique_ptr<std::mutex>
// - std::shared_ptr<T> semantics:
//     - class Game: public std::enable_shared_from_this<Game>
//     - shared_from_this() as a shared_ptr which mutually owns the same object
//     (Player player1( "Jeeves",  board_, shared_from_this(), headsOrTailsColor(), mainMutex_ );
// - ...

// Multithreading:
// - all keyboard events are being processed independently in separate thread

// Object Oriented Design:
// - all pieces derived from abstract base class Piece
// - all significant entities are objects: board, pieces, players, console, game

// Tricks:
// - Pointers to member functions (040119 replaced with STRATEGY pattern)
//   ( Player::* whitePlayer )( int32_t&, int32_t&, int32_t&, int32_t& ) =
//   ( ch - 48 == 1 ? &Player::makeManualMove : &Player::makeRandomTestMove );

// TODO:
// KING: is immortal now. Make him mortal.
// KING: teach king to hide from check or to surrender certain player if mate occurs.
// KING: check if lineBetween (king, rook) != lineUnderAttack while casting
// AI:   more AI for better play.

#ifndef CPPHESS
#define CPPHESS

#include <cstdint>
#include <iostream>    // Basic IO
#include <iomanip>     // Console / IO / setw
#include <typeinfo>    // Types distinction check.

#include <vector>
#include <algorithm>   // std::shuffle

#include <random>      // uniform_int_distribution, bernoulli_distribution

#include <cmath>       // min()
#include <cassert>

#include <mutex>
#include <thread>
#include <memory>


#ifdef __linux__ 
  #include "conio.h"     // Console / IO / _kbhit() _getch()

#elif _WIN32
  #include <conio.h>     // Console / IO / _kbhit() _getch()
  #include <windows.h>   // Console / WinAPI
#else
#endif


// #include <curses.h>

class Piece;
class Player;
class Board;
class Game;

// Start conditions.
static const int32_t START_FRAME         = 1;   // Distance between shown turns.
                                                // E.g. 100 means that first shown
                                                // turn is 1, next shown one is 101.

static const int32_t START_DELAY         = 100; // Delay between frames.
static const int32_t START_BOARD_SIDE    = 8;

// Common constants.
static const int32_t TURNS_MAX           = 1'000'000'000; // Typically it takes 50 turns
                                                          // for classic chess game.
static const int32_t LATIN_ALPHABET_SIZE = 26;

enum class PieceColor : int8_t{ NOT_DEFINED = -1,
                                BLACK,
                                WHITE };



enum class PieceType : int8_t{ NOT_DEFINED = -1,
                               PAWN        = 1,
                               KNIGHT      = 3,
                               BISHOP      = 4,
                               ROOK        = 5,
                               QUEEN       = 9,
                               KING        = 0 };



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



//! \brief Show UTF-8 chess piece image.
void printPiece( const PieceType& PT,
                 const PieceColor& PC = PieceColor::BLACK );



//! \brief Show current pieces on board set.
void show( const std::vector<std::vector<Piece*> >& board );



//! \brief Delay function.
void delay();



//! \brief CLS function.
void clearscr();



//! \brief PieceCoordinates class.
//!
//! Keeps two coordinates:
//! - y (vertical coordinate)
//! - x (horizontal coordinate)
struct PieceCoordinates{

  PieceCoordinates( int32_t y = 0,
                    int32_t x = A_ASCII_CODE ): y_( y ),
                                                x_( x - A_ASCII_CODE ) {}
  static const int32_t A_ASCII_CODE = 'A';
  int32_t y_;
  int32_t x_;
};



//! \brief Exception class GameIsOver.
class GameIsOver{
};



//! \brief std::random_device singleton.
class RandomDevice{
public:
  RandomDevice()                                   = delete;
  RandomDevice( const RandomDevice& )              = delete;
  RandomDevice& operator = ( const RandomDevice& ) = delete;

  static std::random_device* getInstance(){
    if ( rd_ == nullptr )
      rd_ = new std::random_device;

    return rd_;
  }

  static void deleteInstance(){
    if(rd_){
      delete rd_;
      rd_ = nullptr;
    }
  }

private:
  static std::random_device* rd_;
};

class MutexDevice{
public:
  MutexDevice()                                  = delete;
  MutexDevice( const MutexDevice& )              = delete;
  MutexDevice& operator = ( const MutexDevice& ) = delete;

  static std::mutex* getInstance(){
    if ( m_ == nullptr )
      m_ = new std::mutex;

    return m_;
  }

  static void deleteInstance(){
    delete m_;
    m_ = nullptr;
  }

private:
  static std::mutex* m_;
};

class ChoiceDevice{
public:
  ChoiceDevice()                                   = delete;
  ChoiceDevice( const ChoiceDevice& )              = delete;
  ChoiceDevice& operator = ( const ChoiceDevice& ) = delete;

  static void setInstance(int32_t c){
    choice_ = c;
    isChoiceMade_ = true;
  }

  static bool hasInstance(){
    return  isChoiceMade_;
  }

  static int32_t getInstance(){

    // Block - wait until choice is made
    while(!isChoiceMade_){
      std::this_thread::yield();
    }

    isChoiceMade_ = false;
    
    return choice_;
  }

private:
  static int32_t choice_;
  static bool    isChoiceMade_;
};
#endif
