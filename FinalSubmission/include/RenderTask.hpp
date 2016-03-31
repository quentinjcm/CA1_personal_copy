#ifndef RENDERTASK_HPP
#define RENDERTASK_HPP

#include <memory>
#include <random>

#include <ngl/Colour.h>

#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

/// @file RenderTask.hpp
/// @brief File contaiing the RenderTask class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 31/03/2016

/// @class Camera
/// @brief The RenderTask is resposible for rendering a portion of the final image.
/// It uses a mixture of the blin/phong shading model and ray traced reflections and
/// refractions
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
  void renderPixel(double _x, double _y);
  ngl::Colour blinPixel(IsectData *_intersection);
  bool isVisible(ngl::Vec3 _origin, ngl::Vec3 _lightPos);
  ngl::Colour renderPixel(std::vector<ngl::Vec2> pixelSample);
  ngl::Colour traceRay(const Ray &_ray);
  ngl::Vec3 reflect(const ngl::Vec3 _n, const ngl::Vec3 _i);
  ngl::Vec3 refract(const ngl::Vec3 _n, const ngl::Vec3 _i, double _n1, double _n2);
  double rShclick(const ngl::Vec3 _n, const ngl::Vec3 _i, double _n1, double _n2);

private:
  Camera *m_cam;
  Film *m_film;
  std::shared_ptr<Scene> m_scene;
  std::default_random_engine m_generator;
  std::uniform_real_distribution<double> m_distribution;
  int m_xMin;
  int m_yMin;
  int m_xMax;
  int m_yMax;
  int m_aa;
};

#endif//__RENDERTASK_HPP__
