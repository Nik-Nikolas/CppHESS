// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.
//
// Singleton design pattern (see GoF)

#ifndef CPPHESSCLASSESBOARDGLOBALS
#define CPPHESSCLASSESBOARDGLOBALS

#include "C++HESS.h"

class BoardGlobals{
public:

  BoardGlobals() = default;

  static const int32_t& getSize() noexcept{
    return size_;
  }

  static void setSize( const int32_t bsize ) noexcept{
     size_ = bsize;
  }

  static const int32_t& getLongMoveStep() noexcept{
    return longMoveStep_;
  }

  static void setLongMoveStep( const int32_t longMoveStep ) noexcept{
     longMoveStep_ = longMoveStep;
  }

  static const int32_t& getDelay() noexcept{
    return delay_;
  }

  static void setDelay( const int32_t delay ) noexcept{
     delay_ = delay;
  }

  static const int32_t& getFramesStep() noexcept{
    return framesStep_;
  }

  static void setFramesStep( const int32_t framesStep ) noexcept{
     framesStep_ = framesStep;
  }

  static const bool& getGlyphMode() noexcept{
    return isGlyphMode_;
  }

  static void setGlyphMode( const bool isGlyphMode ) noexcept{
     isGlyphMode_ = isGlyphMode;
  }
private:
  static int32_t size_;
  static int32_t longMoveStep_;
  static int32_t delay_;
  static int32_t framesStep_;
  static bool    isGlyphMode_;
};
#endif
