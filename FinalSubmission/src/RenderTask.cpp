#include <memory>
#include <iostream>

#include <ngl/NGLStream.h>

#include <SDL2/SDL.h>

#include "RenderTask.hpp"
#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"

RenderTask::RenderTask(Camera *_cam,
                       Film *_film,
                       std::shared_ptr<Primative> _scene,
                       int _xMin, int _yMin,
                       int _xMax, int _yMax):
  m_cam(_cam),
  m_film(_film),
  m_scene(_scene),
  m_xMin(_xMin),
  m_yMin(_yMin),
  m_xMax(_xMax),
  m_yMax(_yMax)
{
}

void RenderTask::render()
{
  for (int x = m_xMin; x < m_xMax; x++){
    for (int y = m_yMin; y < m_yMax; y++){
      Ray newRay;
      IsectData intersection;
      m_cam->generateRay(x, y, &newRay);
      if (m_scene->intersect(newRay, &intersection)){
        m_film->setDepthPixel(x, y, depthPixel(intersection.m_t));
        m_film->setNormalPixle(x, y, normalPixel(intersection.m_n));
        m_film->setDiffusePixel(x, y, colourPixel(&intersection));
      }
      else{
        m_film->setDepthPixel(x, y, SDL_Color{0, 0, 0, 255});
        m_film->setNormalPixle(x, y, SDL_Color{0, 0, 0, 255});
        m_film->setDiffusePixel(x, y, SDL_Color{0, 0, 0, 255});
      }
    }
  }
}


SDL_Color RenderTask::normalPixel(ngl::Vec3 _normal)
{
  return SDL_Color{clipColour(_normal[0] * 255),
                   clipColour(_normal[1] * 255),
                   clipColour(_normal[2] * -255),
                   255};
}

SDL_Color RenderTask::depthPixel(float _depth)
{
  return SDL_Color{clipColour(_depth),
                   clipColour(_depth),
                   clipColour(_depth),
                   255};
}

SDL_Color RenderTask::colourPixel(IsectData *_intersection)
{
  SDL_Color tmp = _intersection->m_material->getDiffuseColour(_intersection->m_uv[0],
                                                              _intersection->m_uv[1]);
  return tmp;
}

Uint8 RenderTask::clipColour(int n)
{
  return (Uint8)std::max(0, std::min(n, 255));
}


