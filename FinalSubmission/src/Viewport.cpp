#include "Viewport.hpp"
#include "ui_viewport.h"
#include "RenderSettings.hpp"

Viewport::Viewport(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::Viewport)
{
  m_ui->setupUi(this);
  m_settings = new RenderSettings(this);

  connect(m_ui->m_bgR, SIGNAL(valueChanged(double)), m_settings, SLOT(setBGColourR(double)));
  connect(m_ui->m_bgG, SIGNAL(valueChanged(double)), m_settings, SLOT(setBGColourG(double)));
  connect(m_ui->m_bgB, SIGNAL(valueChanged(double)), m_settings, SLOT(setBGColourB(double)));

  connect(m_ui->m_ambientR, SIGNAL(valueChanged(double)), m_settings, SLOT(setAmbientColourR(double)));
  connect(m_ui->m_ambientG, SIGNAL(valueChanged(double)), m_settings, SLOT(setAmbientColourG(double)));
  connect(m_ui->m_ambientB, SIGNAL(valueChanged(double)), m_settings, SLOT(setAmbientColourB(double)));
  connect(m_ui->m_ambientIntensity, SIGNAL(valueChanged(double)), m_settings, SLOT(setAmbientIntensity(double)));

  connect(m_ui->m_camPosX, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamPosX(double)));
  connect(m_ui->m_camPosY, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamPosY(double)));
  connect(m_ui->m_camPosZ, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamPosZ(double)));

  connect(m_ui->m_camAimX, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamAimX(double)));
  connect(m_ui->m_camAimY, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamAimY(double)));
  connect(m_ui->m_camAimZ, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamAimZ(double)));

  connect(m_ui->m_camUpX, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamUpX(double)));
  connect(m_ui->m_camUpY, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamUpY(double)));
  connect(m_ui->m_camUpZ, SIGNAL(valueChanged(double)), m_settings, SLOT(setCamUpZ(double)));

  connect(m_ui->m_aa, SIGNAL(valueChanged(int)), m_settings, SLOT(setAAAmount(int)));
  connect(m_ui->m_maxRayBounces, SIGNAL(valueChanged(int)), m_settings, SLOT(setMaxRayBounces(int)));

  connect(m_ui->m_filmHeight, SIGNAL(valueChanged(int)), m_settings, SLOT(setFilmHeight(int)));
  connect(m_ui->m_filmWidth, SIGNAL(valueChanged(int)), m_settings, SLOT(setFilmWidth(int)));
  connect(m_ui->m_fov, SIGNAL(valueChanged(double)), m_settings, SLOT(setFOV(double)));

  connect(m_ui->m_multiThread, SIGNAL(clicked(bool)), m_settings, SLOT(setMultithread(bool)));
  connect(m_ui->m_threadHeight, SIGNAL(valueChanged(int)), m_settings, SLOT(setThreadHeight(int)));
  connect(m_ui->m_threadWidth, SIGNAL(valueChanged(int)), m_settings, SLOT(setThreadWidth(int)));

  connect(m_ui->m_scenePath, SIGNAL(textEdited(QString)), m_settings, SLOT(setScenePath(QString)));

  connect(m_ui->m_render, SIGNAL(clicked(bool)), m_settings, SLOT(printSettings()));

}

Viewport::~Viewport()
{
  delete m_ui;
  delete m_settings;
}
