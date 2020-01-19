#include "GameFactory.h"

std::shared_ptr<Game> GameFactory::makeGame( std::shared_ptr<Board>& board_,
                                             std::shared_ptr<WinConsole>& cons_,
                                             std::mutex* mutex_ ){
  return std::make_shared<Game>( board_, cons_, mutex_ );
}

std::shared_ptr<Board> GameFactory::makeBoard(){
  return std::make_shared<Board>();
}

std::shared_ptr<WinConsole> GameFactory::makeConsole(  std::mutex* mutex_ ){
  return std::make_shared<WinConsole>( mutex_ );
}
