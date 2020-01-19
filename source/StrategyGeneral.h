// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.
//
// Strategy design pattern (see GoF)

#ifndef CPPHESSCLASSESSTRATEGYGENERAL
#define CPPHESSCLASSESSTRATEGYGENERAL

#include "StrategyInterface.h"

class StrategyGeneral{
public:
  virtual ~StrategyGeneral(){}

  virtual bool playStrategy( int32_t& i,
                             int32_t& j,
                             int32_t& i2,
                             int32_t& j2 ) = 0;

  virtual void setStrategy( const StrategyInterface* s ) = 0;

protected:
  const StrategyInterface* currentStrategy_;
};

#endif
