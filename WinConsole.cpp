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



void WinConsole::showBoard( const Board& board ){
 ::clear();
 ::show( board.read() );
}



void WinConsole::showPlayerData( const Player& player ){
  player.showData();
}



void WinConsole::controlKeyboard( Board& board,
                                  Player& player1,
                                  Game& game,
                                  WinConsole& console ){

  if( _kbhit() ){
    int32_t keyCode = _getch();

    while( _kbhit() )
      _getch();

    static const int32_t STEP = BoardGlobals::getSize();

    switch( keyCode ){
      case 122 :
        if( BoardGlobals::getSize() > STEP ){ // 'z'

          BoardGlobals::setSize( BoardGlobals::getSize() / 2 );
          BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
          board.resetLastMovedPiece();

          board.modify().resize( BoardGlobals::getSize() );

          for( auto i = 0; i < BoardGlobals::getSize(); ++i )
            board.modify()[i].resize( BoardGlobals::getSize() );
        }
        break;
      case 120 : // 'x'
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
      case 110 : // 'n'
        board.clear();
            board.resetLastMovedPiece();
        board.resize();
        King::resetCounter();

        game.reset();
        game.start();
        break;
      case 118 : // 'v'
        if ( 0 == BoardGlobals::getDelay() )
          BoardGlobals::setDelay( 100 );
        else
          BoardGlobals::setDelay( BoardGlobals::getDelay() * 2 );
        break;
      case 99 : // 'c'
        BoardGlobals::setDelay( BoardGlobals::getDelay() / 2 );
        break;
      case 32 : // ' '
        std::cout << " PAUSE MODE - PRINT ANY KEY TO PROCEED:";
        _getch();
        break;
      case 97 : // 'a'
        BoardGlobals::setFramesStep( BoardGlobals::getFramesStep() / 2 );
        break;
      case 115 : // 's'
        BoardGlobals::setFramesStep( BoardGlobals::getFramesStep() * 2 );
        break;
      case 116 :
        BoardGlobals::setGlyphMode( !BoardGlobals::getGlyphMode() );
        break;
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



void WinConsole::delay(){
  ::delay();
}



void WinConsole::clear(){
  ::clear();
}
