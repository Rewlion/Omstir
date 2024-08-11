#include <core/input/input_router.h>
#include <core/log.h>
#include <core/settings.h>
#include <core/time.h>
#include <core/window.h>

void init()
{
  log::init();
  settings::load_app_settings("data/settings.ed");
  clocks::init();
  wnd::init_window();
  input::init_drivers();
  input::Router::init();
}

class TestListener: public input::IInputRouterListener
{
  public:
    TestListener()
    {
      input::Router::registerListener(this);
    }
    ~TestListener()
    {
      input::Router::unregisterListener(this);
    }

    auto onKeyStateChanged(const input::IKeyboard& device,
                             const int key,
                             const bool pressed) -> input::InputRouterProcessStatus override
  {
    loginfo("key:{} pressed:{}", key, pressed);
    return input::InputRouterProcessStatus::ProcessFurther;
  }

  auto getInputRouterPriority() -> int override
  {
    return PRIORITY_DONT_CARE;
  }
};

void close()
{

}

void tick()
{
}

void run()
{
  TestListener tl;

  while (!wnd::has_pending_exit())
  {
    clocks::tick();
    wnd::poll_wnd_messages();
    tick();
  }
}

int main()
{
  init();
  run();
  close();
}
