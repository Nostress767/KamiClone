#define SCf(a) static_cast<float>(a)
#define SCi(a) static_cast<int>(a)
#define SCc(a) static_cast<char>(a)

constexpr int MAIN_MENU = 1;
constexpr int GAME_SCREEN = 2;
constexpr int SETTINGS_MENU = 3;
constexpr int LEFT_MOUSE = 0;
constexpr int RIGHT_MOUSE = 1;
constexpr int MIDDLE_MOUSE = 2;
constexpr float LEFT_SPACE = 1.5; // How many squares/size
constexpr int SCREEN_X_SCALE = 2;
constexpr int SCREEN_Y_SCALE = 2;
constexpr int SQUARE_SIZE = 36;
constexpr int HALF_SQUARE = SQUARE_SIZE / 2;
constexpr int PARITY = SQUARE_SIZE % 2;
constexpr int BOARD_X_OFFSET = SCi(SQUARE_SIZE * (LEFT_SPACE + (PARITY / 2)));
constexpr int BOARD_Y_OFFSET = 0;
constexpr int SQUARE_X_AMOUNT = 16;
constexpr int SQUARE_Y_AMOUNT = 10;
constexpr int SCREEN_X_SIZE = (SQUARE_SIZE * SQUARE_X_AMOUNT) + BOARD_X_OFFSET;
constexpr int SCREEN_Y_SIZE = SQUARE_SIZE * SQUARE_Y_AMOUNT;
constexpr int SQUARE_TOTAL = SQUARE_X_AMOUNT * SQUARE_Y_AMOUNT;
constexpr int BOARD_X_SIZE = SQUARE_SIZE * SQUARE_X_AMOUNT;
constexpr int BOARD_Y_SIZE = SQUARE_SIZE * SQUARE_Y_AMOUNT;
constexpr int LEVELS_AMOUNT = 5;

using LOGICBOARD = std::array<std::array<int, SQUARE_X_AMOUNT>, SQUARE_Y_AMOUNT>;
using VNEIGHBORGRAPH = std::unordered_map<int,std::set<int>>;
using VNPAIR = std::pair<int,std::set<int>>;
using VCPAIR = std::pair<int,int>;
using VCOLORGRAPH = std::unordered_map<int,int>;
using NCGRAPHPAIR = std::pair<VNEIGHBORGRAPH,VCOLORGRAPH>;
using TABTUPLE = std::tuple<int, int, int, LOGICBOARD>;
using XYRANGE = std::array<std::array<int,2>,2>;

const olc::Pixel COLORS[6] = {
olc::Pixel(255, 255, 255),
olc::Pixel(243, 87, 81),
olc::Pixel(70, 57, 38),
olc::Pixel(45, 164, 135),
olc::Pixel(200, 173, 150),
olc::Pixel(233, 175, 30)};

const std::string LEVELS[LEVELS_AMOUNT] = {"\
1 2 10 16 3\n\
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
1 1 1 2 2 2 3 3 1 4 1 3 3 2 1 5\n\
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
