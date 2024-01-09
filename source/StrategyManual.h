// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.
//
// Strategy design pattern (see GoF)

#ifndef CPPHESSCLASSESSTRATEGYMANUAL
#define CPPHESSCLASSESSTRATEGYMANUAL

#include "StrategyInterface.h"

class StrategyManual: public StrategyInterface{
public:
  virtual bool play( std::shared_ptr<Board> board_,
                     std::shared_ptr<Game> game,
                     const Player* player_,
                     int32_t& i,
                     int32_t& j,
                     int32_t& i2,
                     int32_t& j2 ) const;
};

#endif
