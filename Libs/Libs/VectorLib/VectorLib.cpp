#include "pch.h"
#include <cmath>
#include "VectorLib.h"


Vector operator+(Vector vec1, Vector vec2) {
  return Vector(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY());
}

Vector::Vector(Number x_, Number y_) {
  x = x_;
  y = y_;
}
Number Vector::getX() { return x; }
Number Vector::getY() { return y; }	
Number Vector::getModule() {
  return sqrt(x.get() * x.get() + y.get() * y.get());
}
Number Vector::getAngle() { return Number(asin((y / getModule()).get())); }
