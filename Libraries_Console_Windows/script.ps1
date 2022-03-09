cd Number
g++ -c NumberLib.cpp -o NumberLib.o
ar rcs NumberLib.lib NumberLib.o
cp NumberLib.lib ../Vector
cp NumberLib.lib ../Client

cd ..\Vector
g++ -c VectorLib.cpp -o VectorLib.o
g++ VectorLib.o NumberLib.lib -shared -o VectorLib.dll
cp VectorLib.dll ../Client

cd ..\Client
g++ -c Client.cpp -o Client.o
g++ -o client.exe Client.o VectorLib.dll
./client.exe

rm Client.o
rm NumberLib.lib
rm VectorLib.dll
rm client.exe

cd ..\Number
rm NumberLib.lib
rm NumberLib.o

cd ..\Vector
rm NumberLib.lib
rm VectorLib.dll
rm VectorLib.o

cd..