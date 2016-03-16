#ifndef __BBOX_HPP__
#define __BBOX_HPP__

#include <iostream>

#include <ngl/Vec3.h>

#include "Ray.hpp"

/// @file BBox.hpp
/// @brief File contaiing the BBox class which are bounding boxes for the triangle meshes
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016
/// @class BBox
/// @brief The BBox class holds the data for bounding boxes that contain triangle meshes. They
/// also implement the ray/bounding box intersection algorithm to speed up intersection checks
/// for rays. If a ray doesnt intersect the bbox, then it is not checked for intersections with
/// the contained triangles

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
