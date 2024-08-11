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
}

void close()
{

}

void tick()
{
  loginfo("time: {}", clocks::get_sec_since_start());
}

void run()
{
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
