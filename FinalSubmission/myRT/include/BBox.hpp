#ifndef BBOX_HPP
#define BBOX_HPP

#include <iostream>
#include "ngl/Vec3.h"
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
  /// @brief ctor that sets BBox to bound the origin
  BBox();

  /// @brief ctor that creates a BBox around the specified point
  /// @param [in] &_p the point that the BBox will enclose
  BBox(const ngl::Vec3 &_p);

  /// @brief cor that creates a BBox that contains two points
  /// @param [in] &_p1 is the first point in the BBox
  /// @param [in] &_p2 is the second point in the BBox
  BBox(const ngl::Vec3 &_p1, ngl::Vec3 &_p2);

  /// @brief adds a point to an established BBox
  /// @param [in] &_p is the point to add to the BBox
  void addPoint( const ngl::Vec3 &_p);

  /// @brief method for intersecting a ray with the BBox
  /// @param [in] &_ray is the ray that is being tested for intewrsections with the box
  /// @param [out] a boolean that is true if the ray intersected the BBox, and false if else
  bool intersect(const Ray &_ray);

  /// @brief prints the bounds of a bbox, used for debuging and can probably be removed
  void printData();

private:
  /// @brief smallest corner of the BBox
  ngl::Vec3 m_pMin;

  /// @brief largest corner of the BBox
  ngl::Vec3 m_pMax;
};

#endif //__BBOX_HPP__
