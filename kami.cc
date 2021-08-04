#include "includes.h"

//(trying to)Adopt https://google.github.io/styleguide/cppguide.html

class Kami : public olc::PixelGameEngine
{
public:
  std::vector<std::unique_ptr<Scene>> scenes; //Stack-like scenes
  Kami(){sAppName = "Kami";}

public:
  bool OnUserCreate() override
  {
    Clear(olc::BLANK); // Clear layer 0 (nullptr)
    ChangeScene(this,&scenes, kMainMenu);
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    scenes.back()->update_mouse_pos(GetMouseX(), GetMouseY());
    scenes.back()->DrawScene();
    if (scenes.back()->TestForInput()) return scenes.back()->Action();
    return true;
  }

  bool OnUserDestroy() override
  {
    scenes.clear();
    return true;
  }
};

int main()
{
  Kami demo;
  if (demo.Construct(screen_x_size, screen_y_size, screen_x_scale, screen_y_scale))
    demo.Start();
  return 0;
}
