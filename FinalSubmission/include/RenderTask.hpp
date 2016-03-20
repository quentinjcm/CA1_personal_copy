#ifndef __RENDERTASK_HPP__
#define __RENDERTASK_HPP__

#include <memory>

#include <SDL2/SDL.h>

#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"

class RenderTask
{
public:
  RenderTask(Camera *_cam,
             Film *_film,
             std::shared_ptr<Primative> _scene,
             int _xMin, int _yMin,
             int _xMax, int _yMax);
  void render();
  SDL_Color normalPixel(ngl::Vec3 _normal);
  SDL_Color depthPixel(float _depth);
  SDL_Color colourPixel(IsectData *_intersection);
  Uint8 clipColour(int n);
private:
  Camera *m_cam;
  Film *m_film;
  std::shared_ptr<Primative> m_scene;
  int m_xMin;
  int m_yMin;
  int m_xMax;
  int m_yMax;
};

#endif//__RENDERTASK_HPP__
