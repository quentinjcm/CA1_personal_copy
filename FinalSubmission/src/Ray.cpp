#include <limits>

#include <ngl/Vec3.h>

#include "Ray.hpp"

///@file Ray.cpp
///@brief Implementation file for the Ray class

Ray::Ray(ngl::Vec3 _origin, ngl::Vec3 _direction, int _depth):
  m_origin(_origin),
  m_direction(_direction),
  m_invDirection(1.0/m_direction[0],
                 1.0/m_direction[1],
                 1.0/m_direction[2]),
  m_depth(_depth)
{
  //m_direction.normalize();
}

void Ray::setInvDirection()
{
  m_invDirection[0] = 1.0/m_direction[0];
  m_invDirection[1] = 1.0/m_direction[1];
  m_invDirection[2] = 1.0/m_direction[2];
}
