#include "GameFactory.h"

std::shared_ptr<Game> GameFactory::makeGame( std::shared_ptr<Board> board_,
                                             std::shared_ptr<Console> cons__ ){
  return std::make_shared<Game>( board_, cons__ );
}

std::shared_ptr<Board> GameFactory::makeBoard(){
  return std::make_shared<Board>();
}

std::shared_ptr<Console> GameFactory::makeConsole(  std::mutex* mutex_ ){
  return std::make_shared<Console>( mutex_ );
}
