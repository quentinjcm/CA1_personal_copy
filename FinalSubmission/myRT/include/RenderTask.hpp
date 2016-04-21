#ifndef RENDERTASK_HPP
#define RENDERTASK_HPP

#include <memory>
#include <random>
#include <QObject>
#include "ngl/Colour.h"
#include "Film.hpp"
#include "Camera.hpp"
#include "RenderSettings.hpp"
#include "Primative.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

/// @file RenderTask.hpp
/// @brief File contaiing the RenderTask class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 09/04/2016

/// @class RenderTask
/// @brief The RenderTask is resposible for rendering a portion of the final image.
/// It uses a mixture of the blin/phong shading model and ray traced reflections and
/// refractio. It is contructed with a range of x and y pixels that it is resposible
/// for rendering
class RenderTask
{
public:
  /// @brief ctor that takes in everything needed by the rendertask
  /// @param [in] *_cam a pointer to the camera used to construct rays
  /// @param [in] *_film a pointer to the film where the outputed pixels will be stored
  /// @param [in] _scene a shared pointer to the scene that is to be rendered
  /// @param [in] _xMin is the minimum x pixel that the render task will render
  /// @param [in] _yMin is the minimum y pixel that the render task will render
  /// @param [in] _xMax is the maximum x pixel that the render task will render
  /// @param [in] _yMax is the maximum y pixel that the render task will render
  /// @param [in] _settings is the RenderSettings object that the render task will use
  RenderTask(Camera *_cam,
             Film *_film,
             std::shared_ptr<Scene> _scene,
             int _xMin, int _yMin,
             int _xMax, int _yMax,
             std::shared_ptr<RenderSettings> _settings);

  /// @brief main function that is called to render the range of pixels for this render task
  void render();

  private:
  /// @brief renders a single pixel in the final image
  /// @param [in] pixelSample is a vector of points that will be rendered and averaged to
  /// produce a final colour. the amout of samples taken is defined by the aa box in the ui
  /// @param [out] the averaged colour for the given vector of samples
  ngl::Colour renderPixel(std::vector<ngl::Vec2> pixelSample);

  /// @brief calulates the colour value for blin shading at the point defined in the intersection data
  /// @param [in] *_intersection is a data structure that holds all of the informatin required to shade a point of intersection
  /// @param [out] the colour value that has been calulated
  ngl::Colour blinnPixel(IsectData *_intersection);

  /// @brief a function that checks for a direct line of sight between a point and a light, used to calulate shaddows
  /// @param [in] _origin is the pont being checked for shaddows
  /// @param [in] _lightPos is the position of the light being checked for visibility
  /// @param [out] returns true if there is nothing blocking the light from the point of origin
  bool isVisible(ngl::Vec3 _origin, ngl::Vec3 _lightPos);

  /// @brief traces a single ray into the scene and returns the colour value for that ray
  /// @param [in] &_ray is the ray to be traced into the scene
  /// @param [out] returns the colour value for the given ray
  ngl::Colour traceRay(const Ray &_ray);

  /// @brief calulates a direction vector for a reflected ray with given incident normal and incoming direction
  /// @param [in] _n is the normal of the geometry at the point of intersection
  /// @param [in] _i is the incoming direction of the ray
  /// @param [out] returns a vec3 that is the outgoing direction of the reflected ray
  ngl::Vec3 reflect(const ngl::Vec3 _normal, const ngl::Vec3 _incident);

  /// @brief calulates a direction vector for a refracted ray with given incident normal and incoming direction
  /// @param [in] _n is the normal of the geometry at the point of intersection
  /// @param [in] _i is the incoming direction of the ray
  /// @param [out] returns a vec3 that is the outgoing direction of the refracted ray
  ngl::Vec3 refract(const ngl::Vec3 _normal, const ngl::Vec3 _incident, double _n1, double _n2);

  /// @brief calulates an approximation to the fresnel factor using shclicks approximation
  /// @param [in] _n is the normal for the given point
  /// @param [in] _i is the incident vector
  /// @param [in] _n1 is the refractive index of the medium the ray is coming from
  /// @param [in] _n2 is the refractive index of the medium the ray is colliding with
  double rShclick(const ngl::Vec3 _normal, const ngl::Vec3 _incident, double _n1, double _n2);

  /// @brief fills the given vector with randomly generated smaples to be passed to the renderer
  /// @param [in] *_samples is a pointer to a vector that is to be filled up with sample
  void generateAASamples(const int _x, const int _y, std::vector<ngl::Vec2> *_samples);

  /// @brief pointer to the camera that will generate the initial rays
  const Camera *m_cam;

  /// @brief pointer to the film where the final image will be stored
  Film *m_film;

  /// @brief shared pointer to the scene that is to be rendered
  const std::shared_ptr<Scene> m_scene;

  /// @brief shared pointer to the render settings structure
  const std::shared_ptr<RenderSettings> m_settings;

  /// @brief the render taks random number generator for random sampling
  std::mt19937 m_generator;

  /// @brief the random number generators distribution
  std::uniform_real_distribution<double> m_distribution;

  /// @brief smallest x coordinate of a pixel in the render task
  int m_xMin;

  /// @brief smallest y coordinate of a pixel in the render task
  int m_yMin;

  /// @brief largest x coordinate of a pixel in the render task
  int m_xMax;

  /// @brief largest y coordinate of a pixel in the render task
  int m_yMax;
};

#endif
