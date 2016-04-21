#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <memory>
#include <vector>
#include "RenderTask.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "RenderSettings.hpp"

/// @file Renderer.hpp
/// @brief File contaiing the Renderer class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 27/03/2016

/// @class Renderer
/// @brief The Renderer class is responible for setting up the rednering of the final image
/// it does this by setting up render tasks for groups of pixels, then rendering each of the
/// tasks. The reason for the task structure is that it makes it very easy to multithread
/// the program, while also giving the option of not multithreading if required
class Renderer
{
public:
  /// @brief ctor that initialises variables in the renderer
  /// @param [in] _scene a shared pointer to the scene that the renderer will render
  /// @param [in] _settings is a renders ettings object with all of the settings set by the usere in the ui
  /// @param [in] *_film the film that the renderer will use to store the outputed pixels
  Renderer(std::shared_ptr<Scene> _scene, std::shared_ptr<RenderSettings> _settings, Film *_film);

  /// @brief method to set up and render the vecotr of render tasks
  void renderImage();

private:
  /// @brief film to render to
  Film *m_film;

  /// @brief camera to render from
  Camera m_cam;

  /// @brief scene to render
  const std::shared_ptr<Scene> m_scene;

  /// @brief tasks to build up and render
  std::vector<RenderTask> m_tasks;

  /// @brief shared pointer to the render settings set by the gui
  const std::shared_ptr<RenderSettings> m_settings;
};

#endif
