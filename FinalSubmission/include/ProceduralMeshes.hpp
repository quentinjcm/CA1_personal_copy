#ifndef __PROCEDURALMESHES_HPP__
#define __PROCEDURALMESHES_HPP__

#include <memory>

#include <ngl/Vec3.h>

#include "TriangleMesh.hpp"

/// @file ProceduralMeshes.hpp
/// @brief File contaiing the ProceduralMeshes class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 22/03/2016

/// @class ProceduralMeshes
/// @brief a class that contains functions for generating procedural meshes
class ProceduralMeshes
{
public:
  /// @brief constructs a plane in the x, z plane with uvs and normals
  /// @param [in] _width is the length of the plane in the x direction
  /// @param [in] _height is the length of the plane in the z direction
  /// @param [out] a shared pointer to the triangle mesh that has been created
  static std::shared_ptr<TriangleMesh> pPlane(float _width, float _height);

  /// @brief constructs a sphere centerd at the origin with normals and uvs
  /// @param [in] _r is the radius of the sphere
  /// @param [in] _sd is the number of subdivision of the sphere
  /// @param [out] a shared pointer to the triangle mesh that has been created
  static std::shared_ptr<TriangleMesh> pSphere(float _r, int _sd);

private:
  /// @brief converts a psoition in spherical coordinates to cartesian
  /// @param [in] _theta is one component of the spehrical coordinates
  /// @param [in] _phi is the second component of the circular coordinates
  /// @param [out] a ngl::Vec3 with the x, y and x coordinated of the point in cartesian space
  static ngl::Vec3 circularToCartesian(float _theta, float _phi);
};

#endif//__PROCEDURALMESHES_HPP__
