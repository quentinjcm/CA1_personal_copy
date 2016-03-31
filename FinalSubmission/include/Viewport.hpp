#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QMainWindow>
#include "RenderSettings.hpp"
#include "NGLWindow.hpp"

namespace Ui {
class Viewport;
}

class Viewport : public QMainWindow
{
  Q_OBJECT

public:
  explicit Viewport(QWidget *parent = 0);
  ~Viewport();

private:
  Ui::Viewport *m_ui;
  RenderSettings *m_settings;
};

#endif // VIEWPORT_H
