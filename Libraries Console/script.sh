#!/bin/bash
cd Number
g++ -c library.cpp -o lib_number.o
ar rcs lib_number.a lib_number.o
cp lib_number.a	../Vector
cp lib_number.a ../Client

cd ../Vector
g++ -c library.cpp -o lib_vector.o
g++ lib_vector.o lib_number.a -shared -o lib_vector.so
cp lib_vector.so ../Client

cd ../Client
g++ -c main.cpp -o main.o
g++ -o main main.o lib_number.a lib_vector.so
sudo mv lib_vector.so /usr/lib
./main

rm main.o
rm lib_number.a
rm main

cd ../Number
rm lib_number.a
rm lib_number.o
rm number.o

cd ../Vector
rm lib_number.a
rm lib_vector.o
rm lib_vector.so

cd ..
