#include <core/log.h>
#include <core/window.h>
#include <core/settings.h>

void init()
{
  log::init();
  settings::load_app_settings("data/settings.ed");
  wnd::init_window();
}

void close()
{

}

void run()
{
  loginfo("hw");

  while (!wnd::has_pending_exit())
  {
    wnd::poll_wnd_messages();
  }
}

int main()
{
  init();
  run();
  close();
}
