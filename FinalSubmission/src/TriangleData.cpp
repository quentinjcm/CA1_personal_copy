#include <ngl/Vec3.h>
#include <ngl/Vec2.h>

#include "TriangleData.hpp"

TriangleData::TriangleData(ngl::Vec3 _n0, ngl::Vec3 _n1, ngl::Vec3 _n2,
                           ngl::Vec2 _uv0,ngl::Vec2 _uv1,ngl::Vec2 _uv2):
  m_n0(_n0), m_n1(_n1), m_n2(_n2),
  m_uv0(_uv0), m_uv1(_uv1), m_uv2(_uv2)
{
}
