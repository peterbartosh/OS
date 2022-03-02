#pragma once

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
