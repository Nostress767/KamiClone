#ifndef _KAMI_FUNC_PROTOTYPES_H_
#define _KAMI_FUNC_PROTOTYPES_H_

#include "olcPixelGameEngine.h"
#include "const_definitions.h"
#include "class_prototypes.h"
#include "class_definitions.h"
#include <tuple>

bool SaveChanges(std::vector<std::unique_ptr<RectButton>>& buttons);
void ChangeScene(olc::PixelGameEngine* pge,std::vector<std::unique_ptr<Scene>>* scenes, int scene, int level = 0);
int Pow(int x, unsigned int p);
void MergeEdge(VertexNeighborGraph &G, int i, int j);
GraphPair GenerateGraph(LogicBoard T);
GraphPair PaintVertex(VertexNeighborGraph G,VertexColorGraph C,int n, int c);
TableTuple LoadBoard(int level);
void Burn(LogicBoard& array,int l,int c,int original_color);
LogicBoard Paint(LogicBoard tabua, int linha, int coluna, int cor);
bool CheckGameOver(LogicBoard tabuleiro);
std::array<int, 2> Search(VertexNeighborGraph L, VertexColorGraph C, int n_acoes);
std::array<int,3> Hint(LogicBoard T, int acoes);

#endif
