#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <memory>
#include <vector>

#include "RenderTask.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

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
  /// @param [in] *_cam a pointer to the camera that the scene will be rendered from
  /// @param [in] *_film the film that the renderer will use to store the outputed pixels
  /// @param [in] _scene a shared pointer to the scene that the renderer will render
  /// @param [in] _aa the amount of antialiasing that the renderer will do
  Renderer(Camera *_cam, Film *_film, std::shared_ptr<Scene> _scene, int _aa);

  /// @brief method to set up and render the vecotr of render tasks
  void renderImage();

private:
  /// @brief film to render to
  Film *m_film;

  /// @brief camera to render from
  Camera *m_cam;

  /// @brief scene to render
  std::shared_ptr<Scene> m_scene;

  /// @brief tasks to build up and render
  std::vector<RenderTask> m_tasks;

  /// @brief amount of anti aliasing for the renderer to do
  int m_aa;
};

#endif//__RENDERER_HPP__
