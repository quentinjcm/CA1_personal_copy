#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <memory>
#include <vector>

#include "RenderTask.hpp"
#include "Camera.hpp"
#include "TriangleMesh.hpp"
#include "Primative.hpp"
#include "Scene.hpp"

class Renderer
{
public:
  Renderer(Camera *_cam, Film *_film, std::shared_ptr<Scene> _scene, int _aa);
  void renderImage();
private:
  Film *m_film;
  Camera *m_cam;
  std::shared_ptr<Scene> m_scene;
  std::vector<RenderTask> m_tasks;
  int m_aa;
};

#endif//__RENDERER_HPP__
