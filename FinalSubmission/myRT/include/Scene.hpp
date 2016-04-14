#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include "Primative.hpp"
#include "Light.hpp"

/// @file Scene.hpp
/// @brief File contaiing the Scene class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 09/04/2016

/// @class Scene
/// @brief the scene class holds all of the primatives and lights in the scene.
class Scene: public Primative
{
public:
  /// @brief intersection method that fills the intersection structure with data on the intersection
  /// @param [in] &_ray is the ray being tested for intersection
  /// @param [in] *_intersection is a data strucutre to be filled with data on the intersection
  /// @param [out] returns a bool that is true if an intersection has occoured
  bool intersect(const Ray &_ray, IsectData *_intersection);

  /// @brief An intersection method for shaddow rays, which dont need to return data about the intersection,
  /// just return if there is somethign blocking the light along the ray
  /// @param [in] the ray to be checked for intersection with the scene
  /// @param [out] a bool that is true if the ray intersected geometry within the range specified by the ray
  bool sIntersect(const Ray &_ray);

  /// @brief adds a primative to the primative vector
  /// @param [in] _prim is the primative to be added to the scene
  void addPrim(std::shared_ptr<Primative> _prim){ m_sceneGeo.push_back(_prim); }

  /// @brief adds a light to the vector of lights in the scene
  /// @param[in] _light is the light to be added to the scene
  void addLight(Light _light){ m_sceneLights.push_back(_light); }

  /// @brief fills two vectors up with points and normals for all the geometry in the scene, this will be
  /// used in the opengl viewport
  /// @param [in] *_points is a vector to be filled up with point positions
  /// @param [in] *_normals is a vector to be filled up with normal vectors
  void getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals);

  /// @brief gets the vector of lights in the scene
  /// @param [out] a pointer to the vector of lights
  std::vector<Light>* getLights(){ return &m_sceneLights; }

private:
  /// @brief the vector of lights ontained in the scene
  std::vector<Light> m_sceneLights;

  /// @brief the vector of shared pointers to the scene geometey
  std::vector<std::shared_ptr<Primative>> m_sceneGeo;
};

#endif//SCENE_HPP
