#include "assert.h"

#include <winuser.h>
#include <stacktrace>

void show_assert_window(string error, const bool isIgnorable)
{
  error += "\n\n";
  error += std::to_string(std::stacktrace::current());

  logerr(error);

  int flags = MB_ICONERROR | MB_DEFBUTTON2;
  flags |= isIgnorable ? MB_ABORTRETRYIGNORE : MB_OK;

  const int msgboxID = MessageBox(NULL, error.c_str(), "Error", flags);

  switch (msgboxID)
  {
    case IDIGNORE:
      if (isIgnorable)
        break;
    case IDOK:
    case IDRETRY:
    case IDABORT:
        exit(-1);
        break;
  }
}