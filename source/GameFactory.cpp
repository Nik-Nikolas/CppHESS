#include "GameFactory.h"

std::shared_ptr<Game> GameFactory::makeGame( std::shared_ptr<Board> board,
                                             std::shared_ptr<Console> cons ){
  return std::make_shared<Game>( board, cons );
}

std::shared_ptr<Board> GameFactory::makeBoard(){
  return std::make_shared<Board>();
}

std::shared_ptr<Console> GameFactory::makeConsole(  std::mutex* mutex ){
  return std::make_shared<Console>( mutex );
}
