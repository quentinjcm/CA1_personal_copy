#ifndef __BBOX_HPP__
#define __BBOX_HPP__

#include <iostream>

#include <ngl/Vec3.h>

#include "Ray.hpp"

class BBox
{
public:
  BBox();
  BBox(const ngl::Vec3 &_p);
  BBox(const ngl::Vec3 &_p1, ngl::Vec3 &_p2);
  void addPoint( const ngl::Vec3 &_p);
  bool intersect(const Ray &_ray);
  void printData();
private:
  ngl::Vec3 m_pMin;
  ngl::Vec3 m_pMax;
};

#endif //__BBOX_HPP__
