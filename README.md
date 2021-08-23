Dependencies: olcPixelGameEngine (https://github.com/OneLoneCoder/olcPixelGameEngine)

Just include the source header file to compile.

For Windows using MSVC: cl /std:c++latest /EHsc kami.cc

For Linux: g++ kami.cc -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20
