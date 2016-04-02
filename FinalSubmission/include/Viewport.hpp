#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <memory>

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
  Viewport(QWidget *parent = 0);
  ~Viewport();

private:
  Ui::Viewport *m_ui;
  std::shared_ptr<RenderSettings> m_settings;
};

#endif // VIEWPORT_H
