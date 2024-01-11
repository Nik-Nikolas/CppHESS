// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.

#include "Player.h"
#include "Board.h"
#include "Console.h"

#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include <exception>

void Console::setFont( const int32_t font ){

#ifdef __linux__ 

#elif _WIN32
  static HMODULE hmod = GetModuleHandleA( "KERNEL32.DLL" );
  typedef BOOL ( WINAPI* SETCONSOLEFONT )( HANDLE, DWORD );
  static SETCONSOLEFONT SetConsoleFont =
  ( SETCONSOLEFONT ) GetProcAddress( hmod, "SetConsoleFont" );

  // console font (2, 6, 9-seems good) scale
  SetConsoleFont( GetStdHandle( STD_OUTPUT_HANDLE ), font );
  system( "mode con cols=600 lines=400" );
#else
#endif
}



void Console::showBoard( const std::shared_ptr<Board> board ) const{
 ::clearscr();
 ::show( board->read() );
}



void Console::showPlayerData( const Player& player ) const{
  player.showData();
}



void Console::controlKeyboard( std::shared_ptr<Board> board,
                                  std::shared_ptr<Game> currentGame ){
  while( true ){
    if(getConsoleInputMode() == ConsoleInputMode::ASYNC){
      if( _kbhit() ){

        int32_t keyCode = _getch();

        static const int32_t STEP = BoardGlobals::getSize();

        switch( keyCode ){
          // 'z'
          case 122 :
            if( BoardGlobals::getSize() > STEP ){

              BoardGlobals::setSize( BoardGlobals::getSize() / 2 );
              BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
              board->resetLastMovedPiece();

              board->modify().resize( BoardGlobals::getSize() );

              for( auto i = 0; i < BoardGlobals::getSize(); ++i )
                board->modify()[i].resize( BoardGlobals::getSize() );
            }
            break;
          // 'x'
          case 120 :

            BoardGlobals::setSize( BoardGlobals::getSize() * 2 );
            BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
            board->resetLastMovedPiece();

            board->modify().resize( BoardGlobals::getSize() );

            for( auto i = 0; i < BoardGlobals::getSize(); ++i )
              board->modify()[i].resize( BoardGlobals::getSize() );

            //for( auto i = BoardGlobals::getSize() - STEP; i < BoardGlobals::getSize(); ++i )
            //  for( auto j = BoardGlobals::getSize() - STEP; j < BoardGlobals::getSize(); ++j )
            //    board.modify()[i][j] = nullptr;

            break;
          // 'n'
          case 110 :

            // Clear all board data
            board->clear();
            board->resetLastMovedPiece();
            board->resize();

            // Clear King data
            King::resetCounter();

            // Set invalid status. Then game will notice it in main thread -
            // it will throw exception
            currentGame->setInvalid();

            break;
          // 'v'
          case 118 :
            if ( 0 == BoardGlobals::getDelay() )
              BoardGlobals::setDelay( 100 );
            else
              BoardGlobals::setDelay( BoardGlobals::getDelay() * 2 );
            break;
          // 'c'
          case 99 :
            BoardGlobals::setDelay( BoardGlobals::getDelay() / 2 );
            break;
          // space
          case 32 :
            ChoiceDevice::setInstance(keyCode);
             break;
          // 'a'
          case 97 :
            BoardGlobals::setFramesStep( BoardGlobals::getFramesStep() / 2 );
            break;
          // 's'
          case 115 :
            BoardGlobals::setFramesStep( BoardGlobals::getFramesStep() * 2 );
            break;
          // 't'
          case 116 :
            BoardGlobals::setGlyphMode( !BoardGlobals::getGlyphMode() );
            break;
          // ESC
          case 27 :
            exit( 0 );
          default:
            break;
        }

        if ( 0 > BoardGlobals::getDelay() )
          BoardGlobals::setDelay( 0 );

        if ( 0 >= BoardGlobals::getFramesStep() )
          BoardGlobals::setFramesStep( 1 );
      }
    }
    else if(getConsoleInputMode() == ConsoleInputMode::SYNC){
        ChoiceDevice::setInstance(_getch());
    }
    else if(getConsoleInputMode() == ConsoleInputMode::SYNC_ECHO){
        ChoiceDevice::setInstance(_getche());
    }
    else{
      throw std::runtime_error("Unknown console input mode");
    }
  }
}



void Console::delay(){
  ::delay();
}



void Console::clear(){
  ::clearscr();
}



void Console::start( std::shared_ptr<Board> board,
                        std::shared_ptr<Game> game ){

  // Control keyboard in separate thread
  std::thread control ( &Console::controlKeyboard, 
                        this,                         
                        std::ref( board ),            // references to args
                        std::ref( game ) );           // since the function changes board and game objects

  control.detach();

  assert( std::thread::hardware_concurrency() >= 2);
}
