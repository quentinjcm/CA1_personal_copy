#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <memory>

#include <QMainWindow>

#include "RenderSettings.hpp"
#include "Scene.hpp"

/// @file TriangleData.hpp
/// @brief File contaiing the TriangleData class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016

namespace Ui {
class Viewport;
}

/// @class TriangleMesh
/// @brief The viewport class is resposible for setting up the main ui and linking
/// it to a RenderSettings object.
class Viewport : public QMainWindow
{
  Q_OBJECT

public:
  /// @brief ctor that sets the windows parent and initialises the ui, it then goes
  /// theough and links up all of the signals and slots required for the program to run
  /// @param [in] *_parent is the parent qobject of the viewport, this is used by qt for garbage collection
  Viewport(QWidget *_parent = 0);

  /// @brief dtor that deletes the ui object
  ~Viewport();

private:
  /// @brief ui associated with the viewport
  Ui::Viewport *m_ui;

  /// @brief shared pointer to the render settings that the ui will be changing
  std::shared_ptr<RenderSettings> m_settings;

  /// @brief shared pointer to the scene that will be build and rendered through the ui
  std::shared_ptr<Scene> m_scene;

  /// @brief a flag to tell the ui that no scene has been loaded into the ui
  bool m_hasScene;

private slots:
  /// @brief slot that runs the renderer for the currently set scene when the render button is pressed
   void renderCurrent();

   /// @brief slot that loads the scene curently specified in the ui
   void loadScene();
};
#endif //VIEWPORT_H
