#ifndef _KAMI_GAME_LOGIC_H_
#define _KAMI_GAME_LOGIC_H_

#include "olcPixelGameEngine.h"
#include "const_definitions.h"
#include "game_settings.h"
#include "class_prototypes.h"
#include "class_definitions.h"
#include "func_prototypes.h"
#include "method_definitions.h"
#include <tuple>
#include <unordered_map>

bool SaveChanges(std::vector<std::unique_ptr<RectButton>>& buttons){
  bool nothing_changed = true;
  for(auto &button:buttons){
    if(button->special_value==kSquareSize&&square_size!=kSquareSizes[button->value]) {
      nothing_changed = false;
      square_size = kSquareSizes[button->value];
    } else if(button->special_value==kScreenScale&&screen_x_scale!=kScreenScales[button->value]) {
      nothing_changed = false;
      screen_x_scale = kScreenScales[button->value];
      screen_y_scale = screen_x_scale;}}
  return nothing_changed;}
void ChangeScene(olc::PixelGameEngine* pge,std::vector<std::unique_ptr<Scene>>* scenes, int scene, int level){
  if (scenes->size() > 1) {
    if (scene == kSettingsMenu) {
      while(scenes->back()->type != kSettingsMenu){
        scenes->pop_back();}
    } else if (scene == kMainMenu && scenes->back()->type != kMainMenu) {
      scenes->pop_back();
      scenes->push_back(std::make_unique<MainMenu>(pge,scenes));
    } else if (scene == kGameScreen){
      scenes->pop_back();
      if(level < kLevelsAmount) scenes->push_back(std::make_unique<Game>(pge,scenes,level));
      else scenes->push_back(std::make_unique<MainMenu>(pge,scenes));}
  } else if (scenes->size() == 1) {
    if (scene == kMainMenu) {
      scenes->push_back(std::make_unique<MainMenu>(pge,scenes));
    } else if (scene == kGameScreen){
      scenes->push_back(std::make_unique<Game>(pge,scenes,level));}
  } else {
    scenes->push_back(std::make_unique<SettingsMenu>(pge,scenes));
    scenes->push_back(std::make_unique<MainMenu>(pge,scenes));}}
int Pow(int x, unsigned int p){
  if (p == 0) return 1;
  if (p == 1) return x;

  int tmp = Pow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;}
void MergeEdge(VertexNeighborGraph &G, int i, int j){
  G[j].erase(i);
  G[i].erase(j);
  G[i].insert(G[j].begin(),G[j].end());
  for (auto v: G[j]){
    G[v].erase(j);
    G[v].insert(i);}
  G.erase(j);}
GraphPair GenerateGraph(LogicBoard T){
  VertexNeighborGraph G;
  std::unordered_map<int,int> C;
  // 1Dindex
  // 1Dindex, {1Dindex of square 1 connected to it,1Dindex of square 2 connected to it}
  // 1Dindex, T[line of 1Dindex][column of 1Dindex]
  // Top left corner
  G.insert({0,{1,kSquareX_Amount}});
  C.insert({0,T[0][0]});
  // Top right corner
  int k = kSquareX_Amount-1;
  G.insert({k,{k-1,k+kSquareX_Amount}});
  C.insert({k,T[0][kSquareX_Amount-1]});
  // Bottom left corner
  k = (kSquareY_Amount-1)*kSquareX_Amount;
  G.insert({k,{k-kSquareX_Amount,k+1}});
  C.insert({k,T[kSquareY_Amount-1][0]});
  // Bottom right corner
  k = (kSquareY_Amount-1)*kSquareX_Amount + kSquareX_Amount-1;
  G.insert({k,{k-kSquareX_Amount,k-1}});
  C.insert({k,T[kSquareY_Amount-1][kSquareX_Amount-1]});
  // North edge
  for (int j = 0;j<kSquareX_Amount;j++){
    k = j-1;
    G.insert({k,{k-1,k+1,k+kSquareX_Amount}});
    C.insert({k,T[0][j]});}
  // West edge
  for (int i = 0;i<kSquareY_Amount;i++){
    k = (i-1)*kSquareX_Amount;
    G.insert({k,{k-kSquareX_Amount,k+1,k+kSquareX_Amount}});
    C.insert({k,T[i][0]});}
  // East edge
  for (int i = 0;i<kSquareY_Amount;i++){
    k = (i-1)*kSquareX_Amount+kSquareX_Amount-1;
    G.insert({k,{k-kSquareX_Amount,k-1,k+kSquareX_Amount}});
    C.insert({k,T[i][kSquareX_Amount-1]});}
  // South edge
  for (int j = 0;j<kSquareX_Amount;j++){
    k = (kSquareY_Amount-1)*kSquareX_Amount+j-1;
    G.insert({k,{k-kSquareX_Amount,k-1,k+1}});
    C.insert({k,T[kSquareY_Amount-1][j]});}
  // Center
  for (int i=1;i<kSquareY_Amount-1;i++){
    for (int j=1;j<kSquareX_Amount-1;j++){
      k = i*kSquareX_Amount+j;
      G.insert({k,{k-kSquareX_Amount,k-1,k+1,k+kSquareX_Amount}});
      C.insert({k,T[i][j]});}}
  // Reduce graph by merging same-color neighbors
  bool colapsed = true;
  while (colapsed){
    colapsed = false;
    int U = 0;
    int V = 0;
    for (auto u: G){
      for (auto v: G[u.first]){
        if (C[u.first] == C[v]){U=u.first; V=v; colapsed = true; break;}}
      if (colapsed) break;}
    if (colapsed) {MergeEdge(G, U, V); C.erase(V);}}
  return std::make_pair(G,C);}
GraphPair PaintVertex(VertexNeighborGraph G,VertexColorGraph C,int n, int c){
  VertexNeighborGraph Gp = G;
  VertexColorGraph Cp = C;
  Cp[n] = c;
  for (auto v: G[n]){
    if (C[v] == c){
      MergeEdge(Gp,n,v);
      Cp.erase(v);}}
  return std::make_pair(Gp,Cp);}
TableTuple LoadBoard(int level){
  LogicBoard temparray = {};

  std::array<int,5> metadata = {0, 0, 0, 0, 0}; // level, actions, sizeX, sizeY, colors

  int newline_counter = 0;
  int char_counter = 0;
  int number = 0;
  int numberpower = 0;
  int numbercounter = 0;

  while (newline_counter < kSquareY_Amount+1){
    char current_char = kLevels[level][char_counter];
    char_counter++;
    if (current_char == '\n') {
      if (newline_counter == 0) metadata[numbercounter] = number;
      else temparray[newline_counter-1][numbercounter] = number;
      numbercounter=0; number = 0; numberpower = 0; newline_counter ++; continue;}
    if (current_char == ' ') {
      if (newline_counter == 0) metadata[numbercounter] = number;
      else temparray[newline_counter-1][numbercounter] = number;
      numbercounter++; number = 0; numberpower = 0; continue;}
    number = (number * Pow(10, numberpower)) + static_cast<int>(current_char) - 48;
    numberpower++;}
  return {metadata[0], metadata[1], metadata[4], temparray};}
void Burn(LogicBoard& array,int l,int c,int original_color){
  if (!(l<0||c<0||l>=kSquareY_Amount||c>=kSquareX_Amount)) {
    if (array[l][c] >= 0 && array[l][c] == original_color){
      array[l][c] = -1;
      Burn(array,l-1,c,original_color);
      Burn(array,l,c+1,original_color);
      Burn(array,l+1,c,original_color);
      Burn(array,l,c-1,original_color);}}}
LogicBoard Paint(LogicBoard table, int line, int column, int color){
  Burn(table,line,column,table[line][column]);
  for (int i=0;i<kSquareY_Amount;i++){
    for (int j=0;j<kSquareX_Amount;j++){
      if (table[i][j] == -1) table[i][j] = color;}}
  return table;}
bool CheckGameOver(LogicBoard table){
  for (int i=0;i<kSquareY_Amount;i++){
    for (int j=0;j<kSquareX_Amount;j++){
      if (table[i][j] != table[0][0]) return false;}}
  return true;}
std::array<int, 2> Search(VertexNeighborGraph L, VertexColorGraph C, int n_actions){
  std::array<int,2> deadend = {-1,-1};
  if (n_actions < 0) return deadend;
  if (L.size() == 1){
    int Lkey = 0;
    // map.first = key, map.second = value
    for( const VertexNeighborPair& l : L ) {
      Lkey = l.first;}
    return {Lkey,C[Lkey]};
  } else {
    for( const VertexNeighborPair& l : L ) {
      for( const VertexColorPair& c : C ) {
        if (l.first == c.first) continue;
        GraphPair newLC = PaintVertex(L,C,l.first,c.second);
        if (Search(newLC.first,newLC.second,n_actions-1) == deadend) return {l.first,c.second};}}}
  return deadend;}
std::array<int,3> Hint(LogicBoard T, int n_actions){
  GraphPair LC = GenerateGraph(T);
  std::array<int,2> nc = Search(LC.first,LC.second,n_actions);
  if (nc[0] == -1 || nc[1] == -1) return {0,0,0};
  int i = nc[0] / kSquareX_Amount; int j = nc[0] % kSquareX_Amount;
  return {i,j,nc[1]};}

#endif
