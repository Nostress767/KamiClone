std::ostream &operator<<(std::ostream &os, const SquareIndex& s_i){
  return os << s_i.row << ' ' << s_i.column << '\n';}

void Square::update_offsets(){
  x_offset_ = board_x_offset+(square_size*index_.column);
  y_offset_ = board_y_offset+(square_size*index_.row);
  update_triangles();}
void Square::update_triangles(){
  triangles_[3].v1.x = triangles_[1].v2.x = triangles_[1].v1.x = triangles_[0].v1.x = x_offset_;
  triangles_[2].v1.y = triangles_[1].v1.y = triangles_[0].v2.y = triangles_[0].v1.y = y_offset_;
  triangles_[3].v2.x = triangles_[2].v2.x = triangles_[2].v1.x = triangles_[0].v2.x = x_offset_ + square_size - parity;
  triangles_[3].v2.y = triangles_[2].v2.y = triangles_[3].v1.y = triangles_[1].v2.y = y_offset_ + square_size - parity;

  triangles_[0].v3.x = triangles_[1].v3.x = triangles_[2].v3.x = triangles_[3].v3.x = x_offset_ + half_square;
  triangles_[0].v3.y = triangles_[1].v3.y = triangles_[2].v3.y = triangles_[3].v3.y = y_offset_ + half_square;}
void Square::update_color(olc::Pixel square_color){
  color_ = square_color;}
void Square::update_index(int row_index, int column_index){
  index_.row = row_index; index_.column = column_index;
  update_offsets();}
void Square::DrawSquare(olc::PixelGameEngine* pge){
  pge->FillRectDecal({static_cast<float>(x_offset_), static_cast<float>(y_offset_)}, {static_cast<float>(square_size), static_cast<float>(square_size)}, color_);
  pge->DrawLineDecal({static_cast<float>(x_offset_), static_cast<float>(y_offset_)},{static_cast<float>(x_offset_+square_size), static_cast<float>(y_offset_)}, olc::BLACK);
  pge->DrawLineDecal({static_cast<float>(x_offset_), static_cast<float>(y_offset_)},{static_cast<float>(x_offset_), static_cast<float>(y_offset_+square_size)}, olc::BLACK);}
void Square::DrawTriangle(olc::PixelGameEngine* pge, int t_index){
  olc::Pixel specific_color = olc::GREEN;
  if (t_index == 1){
    specific_color = olc::RED;
  } else if (t_index == 2){
    specific_color = olc::MAGENTA;
  } else if (t_index == 3){
    specific_color = olc::CYAN;
  }
  pge->FillTriangle(triangles_[t_index].v1.x, triangles_[t_index].v1.y, triangles_[t_index].v2.x, triangles_[t_index].v2.y, triangles_[t_index].v3.x, triangles_[t_index].v3.y, specific_color);}

RectButton::RectButton(Scene* s_ptr,int vl,int s_vl,Px p,Px s,olc::Pixel c,std::string t,Px t_p,olc::Pixel t_c,Px t_s,std::string a){
  scene_ptr = s_ptr;
  value = vl;
  special_value = s_vl;
  x_offset = p.x;
  y_offset = p.y;
  x_size = s.x;
  y_size = s.y;
  color = c;
  // Anchor point (tkinter style)
  if (a=="NW"){
    text_x_offset = x_offset+t_p.x;
    text_y_offset = y_offset+t_p.y;
  } else if (a=="N"){
    text_x_offset = x_offset+(x_size/2)+t_p.x-((t.size()*(8*t_s.x))/2);
    text_y_offset = y_offset+t_p.y;
  } else if (a=="NE"){
    text_x_offset = x_offset+x_size+t_p.x-(t.size()*(8*t_s.x));
    text_y_offset = y_offset+t_p.y;
  } else if (a=="W"){
    text_x_offset = x_offset+t_p.x;
    text_y_offset = y_offset+t_p.y+(y_size/2)-(4*t_s.y);
  } else if (a=="C"){
    text_x_offset = x_offset+t_p.x+(x_size/2)-(t.size()*(8*t_s.x))/2;
    text_y_offset = y_offset+t_p.y+(y_size/2)-(4*t_s.y);
  } else if (a=="E"){
    text_x_offset = x_offset+t_p.x+x_size-(t.size()*(8*t_s.x));
    text_y_offset = y_offset+t_p.y+(y_size/2)-(4*t_s.y);
  } else if (a=="SW"){
    text_x_offset = x_offset+t_p.x;
    text_y_offset = y_offset+t_p.y+y_size-(8*t_s.y);
  } else if (a=="S"){
    text_x_offset = x_offset+t_p.x+(x_size/2)-(t.size()*(8*t_s.x))/2;
    text_y_offset = y_offset+t_p.y+y_size-(8*t_s.y);
  } else if (a=="SE"){
    text_x_offset = x_offset+t_p.x+x_size-(t.size()*(8*t_s.x));
    text_y_offset = y_offset+t_p.y+y_size-(8*t_s.y);
  } else{
    text_x_offset = x_offset+t_p.x;
    text_y_offset = y_offset+t_p.y;}
  text = t;
  text_color = t_c;
  text_x_scale = t_s.x;
  text_y_scale = t_s.y;}
XYRange RectButton::get_hitbox(){
  return {x_offset,x_offset+x_size-1,y_offset,y_offset+y_size-1};}
bool RectButton::is_inside(int x, int y){
  if (x<x_offset||x>x_offset+x_size-1||y<y_offset||y>y_offset+y_size-1) return false;
  return true;}
bool RectButton::is_inside(std::array<int,2> x_y){
  if (x_y[0]<x_offset||x_y[0]>x_offset+x_size-1||x_y[1]<y_offset||x_y[1]>y_offset+y_size-1) return false;
  return true;}
void RectButton::update_pos(int x, int y){
  x_offset = x;
  y_offset = y;
  update_text_pos(0,0);}
void RectButton::update_text_pos(int x, int y){
  text_x_offset = x_offset+x;
  text_y_offset = y_offset+y;}
void RectButton::update_size(int x, int y){
  x_size = x;
  y_size = y;}
void RectButton::update_text(std::string& str){
  text = str;}
void RectButton::update_text_color(olc::Pixel new_color){
  text_color = new_color;}
void RectButton::update_color(olc::Pixel new_color){
  color = new_color;}
void RectButton::DrawButton(olc::PixelGameEngine* pge){
  pge->FillRectDecal({static_cast<float>(x_offset),static_cast<float>(y_offset)},{static_cast<float>(x_size),static_cast<float>(y_size)},color);
  if (text!="") DrawText(pge);}
void RectButton::DrawText(olc::PixelGameEngine* pge){
  pge->DrawStringDecal({static_cast<float>(text_x_offset),static_cast<float>(text_y_offset)},text,text_color,{static_cast<float>(text_x_scale),static_cast<float>(text_y_scale)});}

bool SettingsButton::Action(){
  switch (special_value) {
    case kSquareSize: if(value >= 5) value = 0; else value++; break;
    case kScreenScale: if(value>=3) value = 0; else value++; break;
    case kSaveSettings: return SaveChanges(scene_ptr->buttons);}
  return true;}
bool LevelButton::Action(){return true;}
bool ColorButton::Action(){return true;}

Scene::Scene(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr){
  pge_ptr = pge;
  scenes_ptr = s_ptr;
  layer = pge->CreateLayer();
  if(!s_ptr->empty()) pge->EnableLayer(s_ptr->back()->layer, false);
  pge->EnableLayer(layer,true);}
Scene::~Scene(){
  if(scenes_ptr->size()!=1) pge_ptr->EnableLayer((*scenes_ptr)[scenes_ptr->size()-2]->layer, true);
  if(!pge_ptr->GetLayers().empty()) pge_ptr->GetLayers().pop_back();}
void Scene::DrawButtons(){
  for(auto &button: buttons) button->DrawButton(pge_ptr);}
void Scene::update_mouse_pos(int x, int y){
  mouse_pos[0] = x;mouse_pos[1] = y;}
bool Scene::TestForInput(){
  if(pge_ptr->GetMouse(kLeftMouse).bPressed) return true;
  return false;}

SettingsMenu::SettingsMenu(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr) : Scene(pge,s_ptr){
  type = kSettingsMenu;
  CreateButtons();}
void SettingsMenu::DrawScene(){
  pge_ptr->SetDrawTarget(layer);
  pge_ptr->Clear(olc::DARK_BLUE);
  DrawButtons();}
void SettingsMenu::CreateButtons(){
  std::string str1 = "Change Square Size\nCurrent: ";
  str1.push_back(static_cast<char>(square_setting_counter+48));
  std::string str2 = "Change Scale\nCurrent: ";
  str1.push_back(static_cast<char>(screen_setting_counter+48));
  buttons.push_back(std::make_unique<SettingsButton>(this,square_setting_counter,kSquareSize,Px(0,screen_y_size/2),Px(50,50),olc::GREEN,str1));
  buttons.push_back(std::make_unique<SettingsButton>(this,screen_setting_counter,kScreenScale,Px(screen_x_size/2,screen_y_size/2),Px(50,50),olc::GREEN,str2));
  buttons.push_back(std::make_unique<SettingsButton>(this,-1,kSaveSettings,Px(screen_x_size/2,screen_y_size*8/10),Px(50,50),olc::GREEN,"Save Settings"));}
bool SettingsMenu::Action(){
  for(auto &button:buttons){
    if(button->is_inside(mouse_pos)){
      return button->Action();}}
  return true;}

Game::Game(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr,int level) : Scene(pge,s_ptr){
  current_level = level;
  type = kGameScreen;
  for(int i=0;i<kSquareY_Amount;i++){
    for(int j=0;j<kSquareX_Amount;j++){
      renderboard[i][j].update_index(i,j);}}
  LoadLevel();}
void Game::DrawScene(){
  pge_ptr->SetDrawTarget(layer);
  pge_ptr->Clear(olc::BLACK);
  DrawBoard();
  DrawButtons();}
void Game::DrawBoard(){
  //Draw triangle test
  for (int i = 0; i < kSquareY_Amount; i++){
    for (int j=0; j < kSquareX_Amount; j++){
      renderboard[i][j].DrawSquare(pge_ptr);
      //kamiboard[i][j].DrawTriangle(this,0);
      //kamiboard[i][j].DrawTriangle(this,1);
      //kamiboard[i][j].DrawTriangle(this,2);
      //kamiboard[i][j].DrawTriangle(this,3);
}}}
void Game::FindSquare(){
  if (mouse_pos[0] < board_x_offset){
    hovered_square_index.row = -1;
    hovered_square_index.column = -1;
  } else {
    int xcalculation = mouse_pos[0] - board_x_offset;
    int ycalculation = mouse_pos[1] - board_y_offset;
    div_t column = div(xcalculation, square_size);
    div_t row = div(ycalculation, square_size);
    // .quot and .rem
    hovered_square_index.row = row.quot;
    hovered_square_index.column = column.quot;}}
void Game::update_renderboard(){
  for(int i=0;i<kSquareY_Amount;i++){
    for(int j=0;j<kSquareX_Amount;j++){
      renderboard[i][j].update_color(kColors[logicboard[i][j]]);}}}
void Game::update_logicboard(LogicBoard new_board){
  logicboard = new_board;
  update_renderboard();}
void Game::LoadLevel(){
  TableTuple temp = LoadBoard(current_level);
  logicboard = std::get<3>(temp);
  //current_level = std::get<0>(temp);
  n_actions = std::get<1>(temp);
  n_colors = std::get<2>(temp);
  update_logicboard(logicboard);
  CreateButtons();}
void Game::CreateButtons(){
  for(int i=0;i<n_colors;i++){
    buttons.push_back(std::make_unique<ColorButton>(this,i+1,-1,Px(0,(screen_y_size/n_colors)*i),Px(board_x_offset-1,screen_y_size/n_colors),kColors[i+1]));}}
bool Game::Action(){
  for(auto &button:buttons){
    if(button->is_inside(mouse_pos)){
      current_color = button->value;
      return true;}}
  FindSquare();
  if (hovered_square_index.row >= 0 && hovered_square_index.column >= 0){
    update_logicboard(Paint(logicboard, hovered_square_index.row, hovered_square_index.column, current_color));}
  return true;}

MainMenu::MainMenu(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr) : Scene(pge,s_ptr){
  type = kMainMenu;
  CreateButtons();}
void MainMenu::CreateButtons(){
  int counter = 0;
  // Temporary non generic offsets
  std::array<int,5> abc = {screen_x_size/10,(screen_x_size/10)*4,(screen_x_size/10)*7,screen_x_size/10,(screen_x_size/10)*4};
  std::array<int,5> def = {(screen_y_size/12)*1,(screen_y_size/12)*1,(screen_y_size/12)*1,(screen_y_size/12)*6,(screen_y_size/12)*6};
  for(int i=0;i<kLevelsAmount;i++){
    int x_offset = abc[i];
    int y_offset = def[i];
    int x_size = screen_x_size/5;
    int y_size = x_size;
    std::string bt = "Level ";
    bt.push_back(static_cast<char>(i+49));
    buttons.push_back(std::make_unique<LevelButton>(this,i,-1,Px(x_offset,y_offset),Px(x_size,y_size),olc::GREEN,bt));}
    counter+=2;}
bool MainMenu::Action(){
  for(auto &button:buttons){
    if(button->is_inside(mouse_pos)){
      ChangeScene(pge_ptr,scenes_ptr, kGameScreen, button->value);
      return true;}}
  return true;
}
void MainMenu::DrawScene(){
  pge_ptr->SetDrawTarget(layer);
  pge_ptr->Clear(olc::YELLOW);
  DrawButtons();}
