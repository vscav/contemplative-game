#include "include/Application.hpp"

int main()
{
  Application app("Custom application", 1280, 720, false);
  // Application app;
  app.run();

  return 0;
}
