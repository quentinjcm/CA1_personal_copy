#include <iostream>
#include <limits>
#include <algorithm>

#include <ngl/Vec3.h>
#include <ngl/NGLStream.h>

#include "BBox.hpp"
#include "Ray.hpp"

BBox::BBox():
  m_pMin(0, 0, 0),
  m_pMax(0, 0, 0)
{
}

BBox::BBox(const ngl::Vec3 &_p):
  m_pMin(_p),
  m_pMax(_p)
{
}

BBox::BBox(const ngl::Vec3 &_p1, ngl::Vec3 &_p2):
  m_pMin(_p1),
  m_pMax(_p1)
{
  addPoint(_p2);
}

void BBox::addPoint( const ngl::Vec3 &_p)
{
  for (int i: {0, 1, 2}){
    if (_p[i] < m_pMin[i]){
      m_pMin[i] = _p[i];
    }
    else if (_p[i] >  m_pMax[i]){
      m_pMax[i] = _p[i];
    }
  }
}

void BBox::printData()
{
  std::cout << "Printing BBox\n";
  std::cout << "min: "<< m_pMin << "\nmax: " << m_pMax << std::endl;
}

bool BBox::intersect(const Ray &_ray)
{
  float tMin = std::numeric_limits<float>::min();
  float tMax = std::numeric_limits<float>::max();
  for (int i: {0, 1, 2}){
    float t1 = (m_pMin[i] - _ray.m_origin[i]) * _ray.m_invDirection[i];
    float t2 = (m_pMax[i] - _ray.m_origin[i]) * _ray.m_invDirection[i];
    tMin = std::max(tMin, std::min(t1, t2));
    tMax = std::min(tMax, std::max(t1, t2));
  }
  if (tMax >= tMin & tMax > 0 & tMin > 0){
    return true;
  }
  return false;
}
