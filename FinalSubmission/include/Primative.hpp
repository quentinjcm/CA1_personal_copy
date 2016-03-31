#ifndef PRIMATIVE_HPP
#define PRIMATIVE_HPP

#include "Ray.hpp"
#include "IsectData.hpp"

class Primative
{
public:
  virtual bool intersect(const Ray &_ray, IsectData *_intersection);
  virtual bool sIntersect(const Ray &_ray);
private:
};


#endif//__PRIMATIVE_HPP__
