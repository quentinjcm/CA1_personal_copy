#include "Viewport.hpp"
#include "ui_viewport.h"
#include "RenderSettings.hpp"

Viewport::Viewport(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::Viewport)
{
  m_ui->setupUi(this);
  m_settings = std::make_shared<RenderSettings>(this);

  connect(m_ui->m_bgR, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setBGColourR(double)));
  connect(m_ui->m_bgG, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setBGColourG(double)));
  connect(m_ui->m_bgB, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setBGColourB(double)));

  connect(m_ui->m_ambientR, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientColourR(double)));
  connect(m_ui->m_ambientG, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientColourG(double)));
  connect(m_ui->m_ambientB, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientColourB(double)));
  connect(m_ui->m_ambientIntensity, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientIntensity(double)));

  connect(m_ui->m_camPosX, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamPosX(double)));
  connect(m_ui->m_camPosY, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamPosY(double)));
  connect(m_ui->m_camPosZ, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamPosZ(double)));

  connect(m_ui->m_camAimX, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamAimX(double)));
  connect(m_ui->m_camAimY, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamAimY(double)));
  connect(m_ui->m_camAimZ, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamAimZ(double)));

  connect(m_ui->m_camUpX, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamUpX(double)));
  connect(m_ui->m_camUpY, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamUpY(double)));
  connect(m_ui->m_camUpZ, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamUpZ(double)));

  connect(m_ui->m_aa, SIGNAL(valueChanged(int)), m_settings.get(), SLOT(setAAAmount(int)));
  connect(m_ui->m_maxRayBounces, SIGNAL(valueChanged(int)), m_settings.get(), SLOT(setMaxRayBounces(int)));

  connect(m_ui->m_filmHeight, SIGNAL(valueChanged(int)), m_settings.get(), SLOT(setFilmHeight(int)));
  connect(m_ui->m_filmWidth, SIGNAL(valueChanged(int)), m_settings.get(), SLOT(setFilmWidth(int)));
  connect(m_ui->m_fov, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setFOV(double)));

  connect(m_ui->m_multiThread, SIGNAL(clicked(bool)), m_settings.get(), SLOT(setMultithread(bool)));
  connect(m_ui->m_threadHeight, SIGNAL(valueChanged(int)), m_settings.get(), SLOT(setThreadHeight(int)));
  connect(m_ui->m_threadWidth, SIGNAL(valueChanged(int)), m_settings.get(), SLOT(setThreadWidth(int)));

  connect(m_ui->m_scenePath, SIGNAL(textEdited(QString)), m_settings.get(), SLOT(setScenePath(QString)));

  connect(m_ui->m_render, SIGNAL(clicked(bool)), m_settings.get(), SLOT(printSettings()));

}

Viewport::~Viewport()
{
  delete m_ui;
}
