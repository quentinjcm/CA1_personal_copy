#include <QApplication>
#include <Viewport.hpp>

#include <vector>

/// @file main.cpp
/// @brief contains the main function that the prigram runs from

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Viewport v;
  v.show();
  return app.exec();

}
