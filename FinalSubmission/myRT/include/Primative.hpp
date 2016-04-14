#ifndef PRIMATIVE_HPP
#define PRIMATIVE_HPP

#include "Ray.hpp"
#include "IsectData.hpp"

/// @file Primative.hpp
/// @brief File contaiing the Primative class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 09/04/2016

/// @class Primative
/// @brief The primatve class in an abstract base class that all primatives in the scene
/// should inherit from. This gives them their basic interface of intersection methods
/// and a function to extract their opengl data. The idea was to ipmlement two primatives
/// which inherit from this, the aggregate primative and the geometric primative. The
/// aggragate primative was to hold other primatives in acceleration structures and the
/// geometric primative holds triangle meshes.While i didnt have time to implement an
/// aggregate primative the setup allows that to happen without too much dificulty and
/// andl enables the easy expansion to othert types of primatives such as nurbs curves and
/// volumes.
class Primative
{
public:
  /// @brief an intersection method that gets the geometric data of the closest intersection
  /// @param [in] &_ray is the ray that is being tested for intersection
  /// @param [in] *_intersection is a data structure that gets filled up with data about the point of intersection
  /// @param [out] a bool to indicate if there was an intersection within the limits defined in the ray
  virtual bool intersect(const Ray &_ray, IsectData *_intersection);

  /// @brief an intersection method that returns as soon as it finds an interection in range for checking shaddow rays
  /// @param [in] &_ray is the ray that is being tested for intersection
  /// @param [out] a bool to indicate if there was an intersection within the limits defined in the ray
  virtual bool sIntersect(const Ray &_ray);

  /// @brief fills up the given vectors with data to be passed to opengl ******why not have vectors of pointers? then there is no copying
  /// @param [in] a vector to be filled up with all of the point position data for ojects in the scene
  /// @param [in] a vector to be filled up with all of the point normals for objects in the scene
  virtual void getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals);
private:
};

#endif//PRIMATIVE_HPP
