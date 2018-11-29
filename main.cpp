#include "C++HESS.h"
#include "Classes.h"

int main(){
  WinConsole console;
  console.initialize();
  Game game;
  Board board;

  Player player1( "Jeeves", &board, &game, game.headsOrTailsColor() );
  Player player2( "Wooster",&board, &game, player1 );
  Player* white = player1.getColor() == PieceColor::WHITE ? &player1 : &player2;
  Player* black = player2.getColor() == PieceColor::BLACK ? &player2 : &player1;

  console.showBoard( board.readBoard() );
  std::cout <<  "Choose scenario 1 - 7 to start (press '-' '+' to change speed "
                "during the game): \n"
                "1 Classic game.\n"
                "2 Kings Battle.\n"
                "3 Queens Battle.\n"
                "4 Pawns Battle.\n"
                "5 Bishop VS Pawn.\n"
                "6 Bishop VS Knight.\n"
                "7 Bishop VS Rook.\n"
                "8 Random Battle: ";

  char ch = '\0';
  std::cin.get( ch );

  player1.arrangePieces( ch - 48 );

  while( game.isRunning() ){
    if( !white->makeRandomMove() ){
      std::cout << "\nWHITES have no pieces or no moves. "
                   "Press ENTER to let BLACKS to move instead.";

       std::cin.get( ch );
    }
    console.showBoard( board.readBoard() );

    if( !black->makeRandomMove() ){
      std::cout << "\nBLACKS have no pieces or no moves. "
                   "Press ENTER to let WHITES to move instead.";

      std::cin.get( ch );
    }

    console.showBoard( board.readBoard() );

    game.nextTurn();
  }

  std::cin.get( ch );

  return 0;
}
