#pragma once
#include "NumberLib.h"

#ifdef VECTORLIB_EXPORTS
#define VECTORLIB_API __declspec(dllexport)
#else
#define VECTORLIB_API __declspec(dllimport)
#endif

class Vector {
 private:
  Number x;
  Number y;

 public:
  VECTORLIB_API Vector() = default;
  VECTORLIB_API Vector(Number x_, Number y_);
  VECTORLIB_API Number getX();
  VECTORLIB_API Number getY();
  VECTORLIB_API Number getModule();
  VECTORLIB_API Number getAngle();
};

const Vector ZERO_V(ZERO_N, ZERO_N);
const Vector ONE_V(ONE_N, ONE_N);


VECTORLIB_API Vector operator+(Vector vec1, Vector vec2);
