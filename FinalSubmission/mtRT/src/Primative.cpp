#include <iostream>
#include "Primative.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"

/// @file Primative.cpp
/// @brief implementation file for the Primative abstract base class

bool Primative::intersect(const Ray &_ray, IsectData *_intersection)
{
  std::cerr << "intersection method for derrived class not defined" << std::endl;
  return false;
}

bool Primative::sIntersect(const Ray &_ray)
{
  std::cerr << "shadow intersection method for derrived class not defined" << std::endl;
  return false;
}

void Primative::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  std::cerr << "getGLData method for derrived class not defined" << std::endl;
}
