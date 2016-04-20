#include <thread>
#include "QGraphicsPixmapItem"
#include "ngl/NGLStream.h"
#include "Viewport.hpp"
#include "ui_viewport.h"
#include "RenderSettings.hpp"
#include "Scene.hpp"
#include "SceneParser.hpp"
#include "Film.hpp"
#include "SDLWindow.hpp"
#include "Renderer.hpp"

Viewport::Viewport(QWidget *_parent) :
  QMainWindow(_parent),
  m_ui(new Ui::Viewport)
{
  // qt setting up the ui
  m_ui->setupUi(this);
  m_renderScene.reset(new QGraphicsScene());
  //m_ui->m_renderView = new QGraphicsView(m_renderScene.get());
  m_renderImage.load("saves/test2.png");
  if (m_renderImage.isNull())
      std::cout << "failed to load image" << std::endl;
  m_pixmapItem.reset(new QGraphicsPixmapItem(QPixmap::fromImage(m_renderImage)));
  m_renderScene->addItem(m_pixmapItem.get());
 // m_ui->m_renderView->show();
  m_ui->m_graphicsLable->setScaledContents( true );

  m_ui->m_graphicsLable->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

  m_ui->m_graphicsLable->setPixmap(QPixmap::fromImage(m_renderImage));
  // initialising the render settings structure that the ui will connect with
  m_settings = std::make_shared<RenderSettings>(this);

  // connecting signals and slots
  connect(m_ui->m_bgR, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setBGColourR(double)));
  connect(m_ui->m_bgG, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setBGColourG(double)));
  connect(m_ui->m_bgB, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setBGColourB(double)));

  connect(m_ui->m_ambientR, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientColourR(double)));
  connect(m_ui->m_ambientG, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientColourG(double)));
  connect(m_ui->m_ambientB, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setAmbientColourB(double)));

  connect(m_ui->m_camPosX, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamPosX(double)));
  connect(m_ui->m_camPosY, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamPosY(double)));
  connect(m_ui->m_camPosZ, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamPosZ(double)));

  connect(m_ui->m_camTargetX, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamTargetX(double)));
  connect(m_ui->m_camTargetY, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamTargetY(double)));
  connect(m_ui->m_camTargetZ, SIGNAL(valueChanged(double)), m_settings.get(), SLOT(setCamTargetZ(double)));

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

  connect(m_ui->m_render, SIGNAL(clicked(bool)), this, SLOT(renderCurrent()));
  connect(m_ui->m_loadScene, SIGNAL(clicked(bool)), this, SLOT(loadScene()));

  connect(m_settings.get(), SIGNAL(taskComplete(int)), m_ui->m_renderProgress, SLOT(setValue(int)));
  connect(m_settings.get(), SIGNAL(totalTasksChanged(int)), m_ui->m_renderProgress, SLOT(setMaximum(int)));
  //connect(m_settings.get(), SIGNAL(totalTasksChanged(int)), m_ui->m_renderProgress, SLOT(reset()));
}

Viewport::~Viewport()
{
}

void Viewport::renderCurrent()
{
  if (m_hasScene){
    std::cout << "rendering scene"  << std::endl;
    Film film(m_settings->m_filmWidth,
                  m_settings->m_filmHeight);
    SDLWindow renderWindow(&film);

    Renderer new_renderer(m_scene, m_settings, &film);

    std::thread renderThread(&Renderer::renderImage, &new_renderer);
    renderThread.detach();
    //new_renderer.renderImage();
    renderWindow.run();
  }
}

void Viewport::loadScene()
{
  std::cout << "loading scene " << m_settings->m_sceneFilePath.toStdString() << std::endl;
  m_scene = std::make_shared<Scene>();

  //parsing the scene specified in the UI's file path
  SceneParser p(m_settings->m_sceneFilePath.toStdString(), m_scene);
  p.parseScene();
  m_hasScene = true;
}
