#ifndef TRIANGLEDATA_HPP
#define TRIANGLEDATA_HPP

#include <ngl/Vec3.h>
#include <ngl/Vec2.h>
#include <ngl/NGLStream.h>
/// @file TriangleData.hpp
/// @brief File contaiing the TriangleData class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016
/// @class TriangleMesh
/// @brief The TriangleData class is used as a container for data for each
/// triange. The idea was to seperate the data that isn't required for intersection
/// tests so that the prefetcher isnt getting unnecessary information and this data
/// is only retrieved once an intersection has been found. This was an attempt to make
/// the program more cache friendly however i dont think it was the right thing to do
/// in this case

/// @class TriangleData
/// @brief A container class that holds normals and texture coordinates for each triangle
class TriangleData
{
public:
  /// @brief ctor that takes in the normals and uv coords for each of the 3 verticies
  /// @param [in] _n0 is the normal corresponding to the first vertex
  /// @param [in] _n1 is the normal corresponding to the second vertex
  /// @param [in] _n2 is the normal corresponding to the third vertex
  /// @param [in] _uv0 is the texture coord corresponding to the first vertex
  /// @param [in] _uv1 is the texture coord corresponding to the second vertex
  /// @param [in] _uv2 is the texture corresponding to the third vertex
  TriangleData(ngl::Vec3 _n0, ngl::Vec3 _n1, ngl::Vec3 _n2,
               ngl::Vec2 _uv0,ngl::Vec2 _uv1,ngl::Vec2 _uv2):
    m_n0(_n0), m_n1(_n1), m_n2(_n2),
    m_uv0(_uv0), m_uv1(_uv1), m_uv2(_uv2){;}

  /// @brief normal for vertex 0
  const ngl::Vec3 m_n0;

  /// @brief normal for vertex 1
  const ngl::Vec3 m_n1;

  /// @brief normal for vertex 2
  const ngl::Vec3 m_n2;

  /// @brief normal for vertex 0
  const ngl::Vec2 m_uv0;

  /// @brief normal for vertex 1
  const ngl::Vec2 m_uv1;

  /// @brief normal for vertex 2
  const ngl::Vec2 m_uv2;
};

#endif//__TRIANGLEDATA_HPP__
