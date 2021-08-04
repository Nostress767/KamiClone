struct SquareIndex{
  int row = 0;
  int column = 0;
  friend std::ostream &operator<<(std::ostream& os, const SquareIndex& s_i);
  SquareIndex(){}
  SquareIndex(int n_x, int n_y){row=n_x;column=n_y;}};
struct Px{
  int x = 0;int y = 0;
  Px(){}
  Px(int n_x, int n_y){x=n_x;y=n_y;}};
struct SquareTriangle{Px v1; Px v2; Px v3;};
struct Scene{
  int layer = 0;
  int type = 0;
  olc::PixelGameEngine* pge_ptr = nullptr;
  std::vector<std::unique_ptr<Scene>>* scenes_ptr = nullptr;
  std::array<int,2> mouse_pos = {};
  std::vector<std::unique_ptr<RectButton>> buttons;
  Scene(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr);
  Scene(){}
  ~Scene();
  void update_mouse_pos(int x, int y);
  virtual void DrawScene() = 0;
  virtual void CreateButtons() = 0;
  virtual bool Action() = 0;
  bool TestForInput();
  void DrawButtons();};

class Square{
  SquareIndex index_ = {};
  //SquareTriangle t1; SquareTriangle t2; SquareTriangle t3; SquareTriangle t4;
  SquareTriangle triangles_[4];
  int x_offset_ = 0;
  int y_offset_ = 0;
  olc::Pixel color_ = olc::WHITE;
  bool use_GPU = true;
  void update_offsets();
  void update_triangles();
public:
  void update_color(olc::Pixel square_color);
  void update_index(int row_index, int column_index);
  void DrawSquare(olc::PixelGameEngine* pge);
  void DrawTriangle(olc::PixelGameEngine* pge, int t_index);};

struct RectButton{
  Scene* scene_ptr = nullptr;
  int value = 0; int special_value = 0;
  int x_offset = 0; int y_offset = 0;
  int text_x_offset = 0; int text_y_offset = 0;
  int x_size = 0; int y_size = 0;
  olc::Pixel color = olc::WHITE; olc::Pixel text_color = olc::BLACK;
  int text_x_scale = 1; int text_y_scale = 1;
  std::string text = "";
  RectButton(Scene* s_ptr,int vl,int s_vl,Px p,Px s,olc::Pixel c = olc::WHITE,std::string t = "",Px t_p = {},olc::Pixel t_c = olc::BLACK,Px t_s = {1,1},std::string a = "C");
  XYRange get_hitbox();
  bool is_inside(int x, int y);
  bool is_inside(std::array<int,2> x_y);
  void update_pos(int x, int y);
  void update_text_pos(int x, int y);
  void update_size(int x, int y);
  void update_text(std::string& str);
  void update_text_color(olc::Pixel new_color);
  void update_color(olc::Pixel new_color);
  void DrawButton(olc::PixelGameEngine* pge);
  void DrawText(olc::PixelGameEngine* pge);
  virtual bool Action() = 0;};

struct SettingsButton: RectButton{
  using RectButton::RectButton;
  bool Action();};

struct LevelButton: RectButton{
  using RectButton::RectButton;
  bool Action();};

struct ColorButton: RectButton{
  using RectButton::RectButton;
  bool Action();};

struct SettingsMenu : public Scene{
  SettingsMenu(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr);
  bool Action();
  void DrawScene();
  void CreateButtons();};

struct MainMenu : public Scene{
  MainMenu(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr);
  void DrawScene();
  void CreateButtons();
  bool Action(); // not yet implemented
};

struct Game : public Scene{
  int current_level = 0;
  int n_actions = 0;
  int n_colors = 0;
  int current_color = 1;
  SquareIndex hovered_square_index = {};
  Square renderboard[kSquareY_Amount][kSquareX_Amount];
  LogicBoard logicboard = {};

  Game(olc::PixelGameEngine* pge, std::vector<std::unique_ptr<Scene>>* s_ptr,int level = 0);
  void update_renderboard();
  void update_logicboard(LogicBoard new_board);
  void DrawScene();
  void CreateButtons();
  bool Action();
  void DrawBoard();
  void FindSquare();
  void LoadLevel();};
