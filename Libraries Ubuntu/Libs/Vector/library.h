#ifndef VECTOR_LIBRARY_H
#define VECTOR_LIBRARY_H

#include "../Number/library.h"


class Vector {
private:
    Number x;
    Number y;

public:
    Vector() = default;
    Vector(Number x_, Number y_);
    Number getX();
    Number getY();
    Number getModule();
    Number getAngle();
};

const Vector ZERO_V(ZERO_N, ZERO_N);
const Vector ONE_V(ONE_N, ONE_N);


Vector operator+(Vector vec1, Vector vec2);


#endif //VECTOR_LIBRARY_H
