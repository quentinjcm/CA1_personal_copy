#ifndef __RENDERTASK_HPP__
#define __RENDERTASK_HPP__

#include <memory>
#include <random>

#include <ngl/Colour.h>

#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

/// @file Camera.hpp
/// @brief File contaiing the Camera class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016

/// @class Camera
/// @brief The Camera class is used to generate rays when passed a screen pixel value as x, y
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
  void renderPixel(float _x, float _y);
  ngl::Colour blinPixel(IsectData *_intersection);
  bool isVisible(ngl::Vec3 _origin, ngl::Vec3 _lightPos);
  ngl::Colour renderPixel(std::vector<ngl::Vec2> pixelSample);
  ngl::Colour traceRay(const Ray &_ray);
  ngl::Vec3 reflect(const ngl::Vec3 _n, const ngl::Vec3 _i);
  ngl::Vec3 refract(const ngl::Vec3 _n, const ngl::Vec3 _i, float _n1, float _n2);
  float rShclick(const ngl::Vec3 _n, const ngl::Vec3 _i, float _n1, float _n2);

private:
  Camera *m_cam;
  Film *m_film;
  std::shared_ptr<Scene> m_scene;
  std::default_random_engine m_generator;
  std::uniform_real_distribution<float> m_distribution;
  int m_xMin;
  int m_yMin;
  int m_xMax;
  int m_yMax;
  int m_aa;
};

#endif//__RENDERTASK_HPP__
