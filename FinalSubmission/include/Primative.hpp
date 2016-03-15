#ifndef __PRIMATIVE_HPP__
#define __PRIMATIVE_HPP__

#include "Ray.hpp"
#include "IsectData.hpp"

class Primative
{
public:
  Primative();
  virtual bool intersect(const Ray &_ray, IsectData *_intersection);
  static uint32_t m_nextPrimId;
private:
  const uint32_t m_primId;
};


#endif//__PRIMATIVE_HPP__
