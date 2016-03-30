#include <iostream>

#include "Primative.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"

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
