#ifndef __RENDERTASK_HPP__
#define __RENDERTASK_HPP__

#include <memory>

#include <SDL2/SDL.h>

#include <ngl/Colour.h>

#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

class RenderTask
{
public:
  RenderTask(Camera *_cam,
             Film *_film,
             std::shared_ptr<Scene> _scene,
             int _xMin, int _yMin,
             int _xMax, int _yMax,
             int _aa);
  void render();
  void renderPixel(int _x, int _y);
  void renderPixelAA(int _x, int _y);
  ngl::Colour normalPixel(ngl::Vec3 _normal);
  ngl::Colour depthPixel(float _depth);
  ngl::Colour colourPixel(IsectData *_intersection);
  ngl::Colour diffuseLighting(IsectData *_intersection);
  ngl::Colour specularLighting(IsectData *_intersection);
  ngl::Colour reflectedLighting(IsectData *_intersection);
  float clipColour(float n);
  bool isVisible(ngl::Vec3 _origin, ngl::Vec3 _lightPos);
  float fSchlick(float f0, ngl::Vec3 _l, ngl::Vec3 _n);
private:
  Camera *m_cam;
  Film *m_film;
  std::shared_ptr<Scene> m_scene;
  int m_xMin;
  int m_yMin;
  int m_xMax;
  int m_yMax;
  int m_aa;
};

#endif//__RENDERTASK_HPP__
