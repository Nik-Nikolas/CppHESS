#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "Board.h"
#include "Game.h"
#include "WinConsole.h"

#include <mutex>
#include<memory>

//! \brief Abstract factory to construct specific objects
class GameFactory
{
  public:
    GameFactory() = default;
    virtual ~GameFactory() = default;

    std::shared_ptr<Game> makeGame( std::shared_ptr<Board>& board_,
                                    std::shared_ptr<WinConsole>& cons_,
                                    std::mutex* mutex_ );

    std::shared_ptr<Board> makeBoard();

    std::shared_ptr<WinConsole> makeConsole(  std::mutex* mutex_ );
};

#endif // GAMEFACTORY_H
