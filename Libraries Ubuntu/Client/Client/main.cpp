#include <iostream>
#include "../../Libs/Number/library.h"
#include "../../Libs/Vector/library.h"

int main() {
    Number number(2);
    Vector vector(number, ONE_N);
    std::cout << number.get() << std::endl;
    std::cout << vector.getModule().get() << std::endl;
    std::cout << vector.getAngle().get() << std::endl;
    return 0;
}
