#ifndef NUMBER_LIBRARY_H
#define NUMBER_LIBRARY_H

class Number {
    float number;

public:
    Number() = default;
    Number(float param);
    Number operator+(Number a);
    Number operator-(Number a);
    Number operator*(Number a);
    Number operator/(Number a);

    float get();
};

Number createNumber(float value);

const Number ONE_N = Number(1);
const Number ZERO_N = Number(0);


#endif //NUMBER_LIBRARY_H
