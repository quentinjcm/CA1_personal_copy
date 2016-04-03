#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <ngl/Vec3.h>
#include <ngl/Vec2.h>
#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>

#include "TriangleData.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"
#include "BBox.hpp"

/// @file Triangle.hpp
/// @brief File contaiing the Triangle class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 11/03/2016
/// @class Triangle
/// @brief The Triangle class is used to represent triangles and implment
/// ray/triangle intersections.

class Triangle
{
public:
  /// @brief ctor for triangle class that takes in positions, normals and uv coords
  /// @param [in] _v0 first point in the triangle
  /// @param [in] _v1 second point in the triangle
  /// @param [in] _v2 third point in the triangle
  /// @param [in] _n0 normal corresponding to the first point in the triangle
  /// @param [in] _n1 normal corresponding to the second point in the triangle
  /// @param [in] _n2 normal corresponding to the third point in the triangle
  /// @param [in] _uv0 tex coord corresponding to the first point in the triangle
  /// @param [in] _uv1 tex coord corresponding to the second point in the triangle
  /// @param [in] _uv2 tex coord corresponding to the third point in the triangle
  Triangle(ngl::Vec3 _v0, ngl::Vec3 _v1, ngl::Vec3 _v2,
           ngl::Vec3 _n0, ngl::Vec3 _n1, ngl::Vec3 _n2,
           ngl::Vec2 _uv0,ngl::Vec2 _uv1,ngl::Vec2 _uv2);

  /// @brief the intersect method for the triangle class
  /// @param [in] &_ray the ray that is being tested for intersections with the triangle
  /// @param [in] *_intersection a data structure th store information about the point of intersection if there is one
  /// @param [out] a boolean that indicates wehter the intersection was successfull
  bool intersect(const Ray &_ray, IsectData *_intersection);

  bool intersectBBox(const Ray &_ray);

  /// @brief a method for printing the information contained within the triangle
  /// can probably be taken out as it was only needed for debuging early on
  void printData();

  /// @brief Vertex 0 of the triangle
  const ngl::Vec3 m_v0;

  /// @brief Vertex 1 of the triangle
  const ngl::Vec3 m_v1;

  /// @brief Vertex 2 of the triangle
  const ngl::Vec3 m_v2;

  std::shared_ptr<TriangleData> m_data;

  private:

  /// @brief Normal to the plane formed from the 3 verticies, calculated at construction
  ngl::Vec3 m_n;

  /// @brief A constant associated with the plane used in intersection calculations.
  /// A plane can be represented using the normal and this constand in the equation
  /// N.P + d = 0 where N is the normal, P is any point on the plane and d is a constant
  /// for the plane.
  double m_d;

  /// @brief One of the minor axes of the normal stored as either 0, 1 or 2. It is
  /// calulated at construction and used to project the triangle onto a plane to make
  /// the intersection calulation faster.
  int m_i1;

  /// @brief The second minor axis of the normal.
  int m_i2;

  /// @brief A function that calulated the normal to the plane from the 3 verticies passed in.
  void calcN();

  /// @brief A function that calulated the constant d in N.P + d = 0 for the plane
  void calcD();

  /// @brief Calculates the dominant axis for the triangles normal. The dominant axis is
  /// the maximum of the absolute x y and x values. This function stores the two remaining
  /// axes in m_i1 and m_i2.
  void calcDominantAxis();

  void getGLData(std::vector<ngl::Vec3> _points, std::vector<ngl::Vec3> _normals);
};

#endif //__TRIANGLE_HPP__
