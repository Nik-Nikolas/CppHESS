#include "C++HESS.h"
#include "Classes.h"

void WinConsole::initialize(){
  static HMODULE hmod = GetModuleHandleA( "KERNEL32.DLL" );
  typedef BOOL ( WINAPI *SETCONSOLEFONT )(HANDLE, DWORD );
  static SETCONSOLEFONT SetConsoleFont = (SETCONSOLEFONT)GetProcAddress( hmod, "SetConsoleFont" );

  SetConsoleFont( GetStdHandle(STD_OUTPUT_HANDLE), 9 );// console font (2, 6, 9-seems good) scale
  system( "mode con cols=900 lines=800" ); //console dimensions
}



void WinConsole::showBoard( const std::vector<std::vector<Piece*> >& board ){
 clear();

 ::show( board );
}



void WinConsole::delay(){
  ::delay();
}



void WinConsole::clear(){
  ::clear();
}
