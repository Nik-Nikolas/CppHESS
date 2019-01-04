// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESSTRATEGY
#define CPPHESSCLASSESSTRATEGY

#include "King.h"

class Strategy{
public:
  virtual ~Strategy(){}
  virtual bool use( Board*& board_, const Player* player_, int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 ) = 0;
};



class Strategy1: public Strategy{
public:
  virtual bool use( Board*& board_, const Player* player_, int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );
};



class Strategy2: public Strategy{
public:
  virtual bool use( Board*& board_, const Player* player_, int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );
};



class Strategy3: public Strategy{
public:
  virtual bool use( Board*& board_, const Player* player_, int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 );
};



class Context{
protected:
  Strategy* operation_;

public:
  virtual ~Context(){}
  virtual bool useStrategy( int32_t& i, int32_t& j, int32_t& i2, int32_t& j2 ) = 0;
  virtual void setStrategy( Strategy* s ) = 0;
};

#endif
