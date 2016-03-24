#ifndef __TRIANGLEDATA_HPP__
#define __TRIANGLEDATA_HPP__

#include <ngl/Vec3.h>
#include <ngl/Vec2.h>

class TriangleData
{
public:
  TriangleData(ngl::Vec3 _n0, ngl::Vec3 _n1, ngl::Vec3 _n2,
               ngl::Vec2 _uv0,ngl::Vec2 _uv1,ngl::Vec2 _uv2);
  const ngl::Vec3 m_n0;
  const ngl::Vec3 m_n1;
  const ngl::Vec3 m_n2;
  const ngl::Vec2 m_uv0;
  const ngl::Vec2 m_uv1;
  const ngl::Vec2 m_uv2;
};

#endif//__TRIANGLEDATA_HPP__
