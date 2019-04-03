// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a cpp file.
#include "Player.h"
#include "Board.h"
#include "WinConsole.h"

void WinConsole::setFont( const int32_t font ){

  static HMODULE hmod = GetModuleHandleA( "KERNEL32.DLL" );
  typedef BOOL ( WINAPI* SETCONSOLEFONT )( HANDLE, DWORD );
  static SETCONSOLEFONT SetConsoleFont =
  ( SETCONSOLEFONT ) GetProcAddress( hmod, "SetConsoleFont" );

  // console font (2, 6, 9-seems good) scale
  SetConsoleFont( GetStdHandle( STD_OUTPUT_HANDLE ), font );
  system( "mode con cols=600 lines=400" );
}



void WinConsole::showBoard( const Board& board ) const{
 ::clear();
 ::show( board.read() );
}



void WinConsole::showPlayerData( const Player& player ) const{
  player.showData();
}



void WinConsole::controlKeyboard( Board& board,
                                  Game& currentGame ){
  while( true ){
    if( _kbhit() ){

      std::lock_guard<std::mutex> guard ( *mainMutex_ );

      // Establish mutex to exclude access from main thread
      //std::lock_guard<std::mutex> guard1( *mainMutex_ );

      int32_t keyCode = _getch();

      while( _kbhit() )
        _getch();

      static const int32_t STEP = BoardGlobals::getSize();

      switch( keyCode ){
        // 'z'
        case 122 :
          if( BoardGlobals::getSize() > STEP ){

            BoardGlobals::setSize( BoardGlobals::getSize() / 2 );
            BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
            board.resetLastMovedPiece();

            board.modify().resize( BoardGlobals::getSize() );

            for( auto i = 0; i < BoardGlobals::getSize(); ++i )
              board.modify()[i].resize( BoardGlobals::getSize() );
          }
          break;
        // 'x'
        case 120 :

          BoardGlobals::setSize( BoardGlobals::getSize() * 2 );
          BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
          board.resetLastMovedPiece();

          board.modify().resize( BoardGlobals::getSize() );

          for( auto i = 0; i < BoardGlobals::getSize(); ++i )
            board.modify()[i].resize( BoardGlobals::getSize() );

          //for( auto i = BoardGlobals::getSize() - STEP; i < BoardGlobals::getSize(); ++i )
          //  for( auto j = BoardGlobals::getSize() - STEP; j < BoardGlobals::getSize(); ++j )
          //    board.modify()[i][j] = nullptr;

          break;
        // 'n'
        case 110 :

          // Clear all board data
          board.clear();
          board.resetLastMovedPiece();
          board.resize();

          // Clear King data
          King::resetCounter();

          // Set invalid status. Then game will notice it in main thread -
          // it throws exception
          currentGame.setInvalid();

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
          std::cout << " PAUSE MODE - PRINT ANY KEY TO PROCEED:";
          _getch();
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
}



void WinConsole::delay(){
  ::delay();
}



void WinConsole::clear(){
  ::clear();
}



void WinConsole::start( Board& board, Game& game ){

  // Multithreading part to split control and main processes.
  //     1. Launch winConsole_->controlKeyboard(...) in separate thread.
  std::thread control ( &WinConsole::controlKeyboard, // pointer to member function
                        this,                   // pointer to obj
                        std::ref( board ),           // references to args
                        std::ref( game ) );          // because function changes board and game objects

  //     2. Detach the thread.
  control.detach();

  assert( std::thread::hardware_concurrency() >= 2);
  // End of multithreading part.
}
