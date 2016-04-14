#include <vector>
#include <QApplication>
#include "Viewport.hpp"

/// @file main.cpp
/// @brief contains the main function that the program runs from

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Viewport v;
  v.show();
  return app.exec();
}
