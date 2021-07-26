struct SquareIndex{
	int row = 0;
	int column = 0;
	friend std::ostream &operator<<(std::ostream& os, const SquareIndex& si);};
struct Px{int x = 0;int y = 0;};
struct SquareTriangle{Px v1; Px v2; Px v3;};

class Square{
	SquareIndex index = {};
	//SquareTriangle t1; SquareTriangle t2; SquareTriangle t3; SquareTriangle t4;
  SquareTriangle triangles[4];
	int xoffset = 0;
	int yoffset = 0;
	olc::Pixel color = olc::WHITE;
  bool use_GPU = true;
	void update_offsets();
	void update_triangles();
public:
  void update_color(olc::Pixel sqrcolor);
  void update_index(int rowindex, int columnindex);
  void draw_square(olc::PixelGameEngine* pge);
  void draw_triangle(olc::PixelGameEngine* pge, int tindex);};

struct RectButton{
	int value = 0;
  int xoffset = 0;
	int yoffset = 0;
  int textxoffset = 0;
	int textyoffset = 0;
  int xsize = 0;
	int ysize = 0;
  olc::Pixel color = olc::WHITE;
  olc::Pixel textcolor = olc::BLACK;
  int textxscale = 1;
  int textyscale = 1;
  std::string text = "";
	RectButton(int vl,Px p,Px s,olc::Pixel c = olc::WHITE,std::string t = "",Px tp = {},olc::Pixel tc = olc::BLACK,Px ts = {1,1},std::string a = "C");
  XYRANGE get_hitbox();
  bool is_inside(int x, int y);
  bool is_inside(std::array<int,2> xy);
  void update_pos(int x, int y);
  void update_text_pos(int x, int y);
  void update_size(int x, int y);
  void update_text(std::string& str);
  void update_textcolor(olc::Pixel newcolor);
  void update_color(olc::Pixel newcolor);
  void draw_button(olc::PixelGameEngine* pge);
  void draw_text(olc::PixelGameEngine* pge);};

struct LevelButton : public RectButton{
	using RectButton::RectButton;
};

struct ColorButton : public RectButton{
	using RectButton::RectButton;
};

struct Game{
	int current_screen = 0;
	olc::PixelGameEngine* pgeptr = nullptr;
	bool main_menu = true;
  std::array<int,2> mouse_pos = {};
	int current_level = 0;
	int n_actions = 0;
	int n_colors = 0;
	int current_color = 1;
	SquareIndex hovered_square_index = {};
	std::vector<ColorButton> color_buttons;
	Square renderboard[SQUARE_Y_AMOUNT][SQUARE_X_AMOUNT];
	LOGICBOARD logicboard = {};
private:
  void update_renderboard();
public:
  Game(olc::PixelGameEngine* pge);
	void draw_board();
	void draw_buttons();
  void update_mouse_pos(int x, int y);
	void find_square();
  void update_logicboard(LOGICBOARD newboard);
  void load_level(int level);
	void change_screen_to(int next_screen);
	bool try_to_paint_square();
	bool try_to_change_color();
	void create_color_buttons();};

struct MainMenu{
	olc::PixelGameEngine* pgeptr = nullptr;
	Game* gameptr = nullptr;
	std::vector<LevelButton> buttons;
	MainMenu(olc::PixelGameEngine* pge,Game* gm);
	void draw_buttons();
	bool try_to_load_level();
};

int pow(int x, unsigned int p);
SquareIndex find_square(int mouse_pos[2]);
void merge_edge(VNEIGHBORGRAPH &G, int i, int j);
NCGRAPHPAIR generate_graph(LOGICBOARD T);
NCGRAPHPAIR paint_vertex(VNEIGHBORGRAPH G,VCOLORGRAPH C,int n, int c);
TABTUPLE load_board(int level);
void burn(LOGICBOARD& array,int l,int c,int originalcolor);
LOGICBOARD paint(LOGICBOARD tabua, int linha, int coluna, int cor);
bool check_game_over(LOGICBOARD tabuleiro);
std::array<int, 2> search(VNEIGHBORGRAPH L, VCOLORGRAPH C, int n_acoes);
std::array<int,3> hint(LOGICBOARD T, int acoes);
