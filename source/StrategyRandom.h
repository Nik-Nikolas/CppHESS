// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.
//
// Strategy design pattern (see GoF)

#ifndef CPPHESSCLASSESSTRATEGYRANDOM
#define CPPHESSCLASSESSTRATEGYRANDOM

#include "StrategyInterface.h"

class StrategyRandom: public StrategyInterface{
public:
  virtual bool play( std::shared_ptr<Board> board_,
                     const Player* player_,
                     int32_t& i,
                     int32_t& j,
                     int32_t& i2,
                     int32_t& j2 ) const;
};

#endif
