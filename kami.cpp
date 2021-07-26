#include "kamiIncludes.hpp"

class Kami : public olc::PixelGameEngine
{
public:
	Game game = Game(this);
	MainMenu main_menu = MainMenu(this,&game);
	Kami(){
		sAppName = "Kami";}
	int menuLayer = 0;
	int gameLayer = 0;

public:
	bool OnUserCreate() override
	{
		game.change_screen_to(MAIN_MENU);
		menuLayer = CreateLayer(); // Layer 1
		gameLayer = CreateLayer(); // Layer 2
		EnableLayer(menuLayer, true);
		EnableLayer(gameLayer, true);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// TODO: make nullptr layer, aka settings layer
    game.update_mouse_pos(GetMouseX(), GetMouseY());
		if (game.current_screen == MAIN_MENU){
			Clear(olc::BLANK);
			SetDrawTarget(menuLayer);
			Clear(olc::YELLOW);
			main_menu.draw_buttons();
			if (main_menu.try_to_load_level()){
				game.change_screen_to(GAME_SCREEN);
			}
		} else if (game.current_screen == GAME_SCREEN){
			Clear(olc::BLANK);
			SetDrawTarget(menuLayer);
			Clear(olc::BLANK);
			SetDrawTarget(gameLayer);
			Clear(olc::BLACK);
			game.draw_board();
			game.draw_buttons();
			// For debugging purposes
			if (GetKey(olc::Key::W).bPressed){
				for(auto m: game.logicboard){
					for(auto n:m){
						std::cout << n;}
					std::cout<<'\n';}
				std::cout<<'\n';}
			// For debugging purposes
			if (GetKey(olc::Key::E).bPressed){
				std::cout<<"Current Color:"<<game.current_color<<" ";
				std::cout<<"n of colors:"<<game.n_colors<<" ";
				std::cout<<"Current Level:"<<game.current_level<<" ";
				std::cout<<"Actions remaining:"<<game.n_actions<<" ";
				std::cout<<'\n';
			}
			game.try_to_change_color();
			game.try_to_paint_square();
		} else if (game.current_screen == SETTINGS_MENU){
			Clear(olc::DARK_BLUE);
		} else{}

		return true;
	}
};

int main()
{
	Kami demo;
	if (demo.Construct(SCREEN_X_SIZE, SCREEN_Y_SIZE, SCREEN_X_SCALE, SCREEN_Y_SCALE))
		demo.Start();
	return 0;
}
