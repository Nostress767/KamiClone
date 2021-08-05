//TODO: (try to)Adopt https://google.github.io/styleguide/cppguide.html

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "const_definitions.h"
#include "game_settings.h"
#include "class_prototypes.h"
#include "class_definitions.h"
#include "func_prototypes.h"
#include "method_definitions.h"
#include "game_logic.h"

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
