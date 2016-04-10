#include <QApplication>
#include <Viewport.hpp>

#include <vector>

/// @file main.cpp
/// @brief contains the main function that the prigram runs from

int main(int argc, char *argv[])
{
  std::vector<int> a = {1, 2, 3};
  std::vector<int> b = {4, 5, 6};
  QApplication app(argc, argv);

  Viewport v;
  v.show();
  return app.exec();

}
