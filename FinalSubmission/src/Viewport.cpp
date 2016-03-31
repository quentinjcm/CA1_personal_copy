#include "Viewport.hpp"
#include "ui_viewport.h"
#include "RenderSettings.hpp"

Viewport::Viewport(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::Viewport)
{
  m_ui->setupUi(this);
  //m_settings = new RenderSettings(this);
  //connect(m_ui->m_wireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  //connect(m_ui->m_render, SIGNAL(clicked(bool)), m_settings, SLOT(printSettings()));

}

Viewport::~Viewport()
{
  delete m_ui;
  delete m_settings;
}
