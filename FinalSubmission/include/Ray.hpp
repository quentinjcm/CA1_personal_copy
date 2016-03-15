#ifndef __RAY_HPP__
#define __RAY_HPP__

#include <ngl/Vec3.h>

/// @file Ray.hpp
/// @brief File contaiing the Ray class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016
/// @class Ray
/// @brief The Ray class holds an origin and direction that define a ray
/// Intersection routines are left up to to the geometric objects

class Ray
{
public:
  /// @brief default ctor so that rays can be created with no values and filled up later
  Ray() = default;

  /// @brief ctor that initialises origin and direction values and normalises the direction
  /// @param [in] _origin is a point that represents the origin of the ray
  /// @param [in] _direction is a vector indicating the direction of the ray
  Ray(ngl::Vec3 _origin, ngl::Vec3 _direction);

  /// @brief sets the inverse direction, 1/m_direction{x, y, z}, to be used in ray/bbox intersections
  void setInvDirection();

  /// @brief origin of the ray
  ngl::Vec3 m_origin;

  /// @brief dirction of the ray
  ngl::Vec3 m_direction;

  /// @brief 1/direction of the ray
  ngl::Vec3 m_invDirection;
};

#endif//__RAY_HPP__
