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
  system( "mode con cols=600 lines=400" ); //console dimensions
}



void WinConsole::showBoard( const Board& board ){

 ::clear();

 ::show( board.readBoard() );
}



void WinConsole::showPlayerData( const Board& board, const Player& player ){
  player.showData();
}



void WinConsole::controlKeyboard( Board& board,
                                  Player& player1,
                                  Game& game,
                                  WinConsole& console ){

  if( _kbhit() ){
    int32_t keyCode = _getch();

    static const int32_t STEP = BoardGlobals::getSize();

    if( 122 == keyCode && BoardGlobals::getSize() > STEP ){ // 'z'

      BoardGlobals::setSize( BoardGlobals::getSize() / 2 );
      BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
      board.resetLastMovedPiece();

      board.changeBoard().resize( BoardGlobals::getSize() );

      for( auto i = 0; i < BoardGlobals::getSize(); ++i )
        board.changeBoard()[i].resize( BoardGlobals::getSize() );

    }
    else if( 120 == keyCode ){ // 'x'
      BoardGlobals::setSize( BoardGlobals::getSize() * 2 );
      BoardGlobals::setLongMoveStep( BoardGlobals::getSize() / 2 );
      board.resetLastMovedPiece();

      board.changeBoard().resize( BoardGlobals::getSize() );

      for( auto i = 0; i < BoardGlobals::getSize(); ++i )
        board.changeBoard()[i].resize( BoardGlobals::getSize() );

      //for( auto i = BoardGlobals::getSize() - STEP; i < BoardGlobals::getSize(); ++i )
      //  for( auto j = BoardGlobals::getSize() - STEP; j < BoardGlobals::getSize(); ++j )
      //    board.changeBoard()[i][j] = nullptr;
    }
    else if( 110 == keyCode ){ // 'n'
      board.clearBoard();
      board.resetLastMovedPiece();
      board.resizeBoard();

      game.reset();
      game.startNewGame( board, console );
    }
    else if( 118 == keyCode ){ // 'v'
      if ( 0 == BoardGlobals::getDelay() )
        BoardGlobals::setDelay( 100 );
      else
        BoardGlobals::setDelay( BoardGlobals::getDelay() * 2 );
    }
    else if( 99 == keyCode ) // 'c'
      BoardGlobals::setDelay( BoardGlobals::getDelay() / 2 );
    else if( 32 == keyCode ){ // ' '
      std::cout << " PAUSE MODE - PRINT ANY KEY TO PROCEED:";
      _getch();
    }
    else if( 97 == keyCode ) // 'a'
      BoardGlobals::setFramesStep( BoardGlobals::getFramesStep() / 2 );
    else if( 115 == keyCode ) // 's'
      BoardGlobals::setFramesStep( BoardGlobals::getFramesStep() * 2 );
    else if( 116 == keyCode )
      BoardGlobals::setGlyphMode( !BoardGlobals::getGlyphMode() );
    else if( 27 == keyCode )
      exit( 0 );

    if ( 0 > BoardGlobals::getDelay() )
      BoardGlobals::setDelay( 0 );

    if ( 0 >= BoardGlobals::getFramesStep() )
      BoardGlobals::setFramesStep( 1 );

    //setFont( BoardGlobals::getSize() > 40 ? 2 : 9 );
  }

  while( _kbhit() ) // Clear cin buff.
    _getch();
}



void WinConsole::delay(){

  ::delay();
}



void WinConsole::clear(){

  ::clear();
}
