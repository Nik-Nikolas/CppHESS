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
  virtual bool use( Board*& board_,
                    const Player* player_,
                    int32_t& i,
                    int32_t& j,
                    int32_t& i2,
                    int32_t& j2 ) const = 0;
};



class Strategy1: public Strategy{
public:
  virtual bool use( Board*& board_,
                    const Player* player_,
                    int32_t& i,
                    int32_t& j,
                    int32_t& i2,
                    int32_t& j2 ) const;
};



class Strategy2: public Strategy{
public:
  virtual bool use( Board*& board_,
                    const Player* player_,
                    int32_t& i,
                    int32_t& j,
                    int32_t& i2,
                    int32_t& j2 ) const;
};



class Strategy3: public Strategy{
public:
  virtual bool use( Board*& board_,
                    const Player* player_,
                    int32_t& i,
                    int32_t& j,
                    int32_t& i2,
                    int32_t& j2 ) const;
};



class Context{
public:
  virtual ~Context(){}

  virtual bool useStrategy( int32_t& i,
                            int32_t& j,
                            int32_t& i2,
                            int32_t& j2 ) = 0; // Pure V.F.

  virtual void setStrategy( const Strategy* s ) = 0;        // Pure V.F.

protected:
  const Strategy* operation_;
};

#endif
