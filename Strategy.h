// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESSTRATEGY
#define CPPHESSCLASSESSTRATEGY

#include "King.h"

class StrategyInterface{
public:
  virtual ~StrategyInterface(){}
  virtual bool play( Board*& board_,
                     const Player* player_,
                     int32_t& i,
                     int32_t& j,
                     int32_t& i2,
                     int32_t& j2 ) const = 0; // Pure V.F.
};



class Strategy1: public StrategyInterface{
public:
  virtual bool play( Board*& board_,
                     const Player* player_,
                     int32_t& i,
                     int32_t& j,
                     int32_t& i2,
                     int32_t& j2 ) const;
};



class Strategy2: public StrategyInterface{
public:
  virtual bool play( Board*& board_,
                     const Player* player_,
                     int32_t& i,
                     int32_t& j,
                     int32_t& i2,
                     int32_t& j2 ) const;
};



class Strategy3: public StrategyInterface{
public:
  virtual bool play( Board*& board_,
                     const Player* player_,
                     int32_t& i,
                     int32_t& j,
                     int32_t& i2,
                     int32_t& j2 ) const;
};



class Strategy{
public:
  virtual ~Strategy(){}

  virtual bool playStrategy( int32_t& i,
                             int32_t& j,
                             int32_t& i2,
                             int32_t& j2 ) = 0; // Pure V.F.

  virtual void setStrategy( const StrategyInterface* s ) = 0; // Pure V.F.

protected:
  const StrategyInterface* currentStrategy_;
};

#endif
