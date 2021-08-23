#ifndef _KAMI_CONST_DEFINITIONS_H_
#define _KAMI_CONST_DEFINITIONS_H_

#include "olcPixelGameEngine.h"
#include <tuple>
#include <set>
#include <unordered_map>

constexpr int kSquareX_Amount = 16;
constexpr int kSquareY_Amount = 10;
constexpr int kLevelsAmount = 5;
constexpr int kMainMenu = 1;
constexpr int kGameScreen = 2;
constexpr int kSettingsMenu = 3;
constexpr int kLeftMouse = 0;
constexpr int kRightMouse = 1;
constexpr int kMiddleMouse = 2;
constexpr float kLeftSpace = 1.5; // How many squares/size

using LogicBoard = std::array<std::array<int, kSquareX_Amount>, kSquareY_Amount>;
using VertexNeighborGraph = std::unordered_map<int,std::set<int>>;
using VertexNeighborPair = std::pair<int,std::set<int>>;
using VertexColorPair = std::pair<int,int>;
using VertexColorGraph = std::unordered_map<int,int>;
using GraphPair = std::pair<VertexNeighborGraph,VertexColorGraph>;
using TableTuple = std::tuple<int, int, int, LogicBoard>;
using XYRange = std::array<std::array<int,2>,2>;

enum Setting {kSquareSize,kScreenScale,kSaveSettings};

const int kSquareSizes[6] = {9,16,25,36,49,64};
const int kScreenScales[4] = {1,2,4,8};
const olc::Pixel kColors[6] = {
olc::Pixel(255, 255, 255),
olc::Pixel(243, 87, 81),
olc::Pixel(70, 57, 38),
olc::Pixel(45, 164, 135),
olc::Pixel(200, 173, 150),
olc::Pixel(233, 175, 30)};
const std::string kLevels[kLevelsAmount] = {"\
1 2 10 16 5\n\
1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2\n\
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3\n\
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3\n\
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3\n\
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3\n\
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3\n\
", "\
2 3 10 16 3\n\
1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2\n\
1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2\n\
3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 1\n\
3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 1\n\
3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 1\n\
3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 1\n\
1 1 1 1 1 1 3 3 3 3 3 3 3 3 3 3\n\
1 1 1 1 1 1 3 3 3 3 3 3 3 3 3 3\n\
", "\
3 2 10 16 3\n\
1 1 1 1 2 2 2 2 2 2 2 2 1 1 1 1\n\
1 1 1 1 2 2 2 2 2 2 2 2 1 1 1 1\n\
1 1 1 1 2 2 2 2 2 2 2 2 1 1 1 1\n\
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n\
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n\
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n\
1 1 1 1 2 2 2 2 2 2 2 2 1 1 1 1\n\
1 1 1 1 2 2 3 3 3 3 2 2 1 1 1 1\n\
1 1 1 1 2 2 3 3 3 3 2 2 1 1 1 1\n\
1 1 1 1 2 2 3 3 3 3 2 2 1 1 1 1\n\
", "\
4 3 10 16 3\n\
1 1 2 2 2 2 2 2 2 2 2 2 2 2 1 1\n\
1 1 2 1 1 1 1 1 1 1 1 1 1 2 1 1\n\
1 1 2 1 3 3 3 3 3 3 3 3 1 2 1 1\n\
1 1 2 1 3 2 2 2 2 2 2 3 1 2 1 1\n\
1 1 2 1 3 2 3 3 3 3 2 3 1 2 1 1\n\
1 1 2 1 3 2 3 3 3 3 2 3 1 2 1 1\n\
1 1 2 1 3 2 2 2 2 2 2 3 1 2 1 1\n\
1 1 2 1 3 3 3 3 3 3 3 3 1 2 1 1\n\
1 1 2 1 1 1 1 1 1 1 1 1 1 2 1 1\n\
1 1 2 2 2 2 2 2 2 2 2 2 2 2 1 1\n\
", "\
5 6 10 16 5\n\
1 1 1 2 2 2 3 3 1 4 1 3 3 2 1 1\n\
1 4 1 1 2 2 2 3 3 1 4 1 3 3 2 1\n\
1 1 4 1 1 2 2 2 3 3 1 4 1 3 3 2\n\
1 1 1 4 1 1 2 2 2 3 3 1 4 1 3 3\n\
4 1 1 1 4 1 1 2 2 2 3 3 1 4 1 3\n\
4 4 1 1 1 4 1 1 2 2 2 3 3 1 4 1\n\
5 4 4 1 1 1 4 1 1 2 2 2 3 3 1 4\n\
5 5 4 4 1 1 1 4 1 1 2 2 2 3 3 1\n\
5 5 5 4 4 1 1 1 4 1 1 2 2 2 3 3\n\
5 5 5 5 4 4 1 1 1 1 1 1 2 2 2 3\n\
"};

#endif
