#include <ngl/Vec3.h>
#include "Ray.hpp"

///@file Ray.cpp
///@brief Implementation file for the Ray class

Ray::Ray(ngl::Vec3 _origin, ngl::Vec3 _direction, int _depth):
  m_origin(_origin),
  m_direction(_direction),
  m_depth(_depth)
{
  setInvDirection();
}

void Ray::setInvDirection()
{
  m_invDirection.m_openGL[0] = 1.0/m_direction.m_openGL[0];
  m_invDirection.m_openGL[1] = 1.0/m_direction.m_openGL[1];
  m_invDirection.m_openGL[2] = 1.0/m_direction.m_openGL[2];
}
