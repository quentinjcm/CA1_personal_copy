#include <iostream>

#include "Primative.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"

uint32_t Primative::m_nextPrimId = 1;

Primative::Primative():
  m_primId(m_nextPrimId)
{
  m_nextPrimId++;
  std::cout << "prim id is " << m_primId << std::endl;
}

bool Primative::intersect(const Ray &_ray, IsectData *_intersection)
{
  std::cerr << "intersection method for derrived class not defined" << std::endl;
  return false;
}
