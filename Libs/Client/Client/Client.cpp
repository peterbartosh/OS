// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"NumberLib.h"
#include"VectorLib.h"

int main() { 
	Number n1(2), n2(3);
  Vector vector(n1, n2);
        std::cout << vector.getX().get() << "  " <<vector.getY().get() << std::endl;
  std::cout << vector.getAngle().get() << "  " << vector.getModule().get()
            << std::endl;
        return 0;
}
