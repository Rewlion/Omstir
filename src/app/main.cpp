#include <core/log.h>

void init()
{
  log::init();
}

void close()
{

}

int main()
{
  init();
  loginfo("hw");
}
