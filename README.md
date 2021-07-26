A C++ clone of the Kami android app

Dependencies: olcPixelGameEngine (https://github.com/OneLoneCoder/olcPixelGameEngine)

Just include the source header file to compile.

For Windows using MSVC: cl /std:c++latest /EHsc kami.cpp

For Linux: g++ kami.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20
