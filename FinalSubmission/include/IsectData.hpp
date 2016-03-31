#ifndef ISECTDATA_HPP
#define ISECTDATA_HPP

#include <memory>

#include <ngl/Vec3.h>
#include <ngl/Vec2.h>

#include "Material.hpp"

/// @file IsectData.hpp
/// @brief File contaiing the IsectData class which are bounding boxes for the triangle meshes
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016

/// @class IsectData
/// @brief a class that holds information about intersection points. All of the attributes
/// are publuc to make accessing them easier. I felt that writing a getter and setter
/// wouldn't add very much and just mean an extra few function calls for every intersection
/// which would potentailly slow the program down.
class IsectData
{
public:
  /// @brief ctor for isect data that sets some default values such as m_t, position and material
  IsectData();

  /// @brief m_t holds ta value that represents the distance along the ray that the intersection occoured
  double m_t;

  /// @brief m_depth holds the bounce depth pf the ray
  int m_depth;

  /// @brief m_pos is the position in world space of the intersection
  ngl::Vec3 m_pos;

  /// @brief  m_n holds the interpolated normal of the intersection point
  ngl::Vec3 m_n;

  /// @brief m_uv holds the interpolated texture coordinate of the intersection point
  ngl::Vec2 m_uv;

  /// @brief m_eyeDir is a vector from the intersection to the rays origin
  ngl::Vec3 m_eyeDir;

  /// @brief m_material is a pointer to the material of the intersected geometry
  std::shared_ptr<Material> m_material;
};

#endif//__ISECTDATA_HPP__
