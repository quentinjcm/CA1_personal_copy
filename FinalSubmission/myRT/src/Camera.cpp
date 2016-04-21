#include <iostream>
#include <cmath>
#include "ngl/Mat4.h"
#include "ngl/Vec3.h"
#include "ngl/Util.h"
#include "ngl/NGLStream.h"
#include "Camera.hpp"
#include "Film.hpp"
#include "Ray.hpp"

/// @file Camera.cpp
/// @brief implementation file for the Camera class

Camera::Camera(ngl::Vec3 _pos,
       ngl::Vec3 _lookAt,
       ngl::Vec3 _up,
       double _fov,
       int _filmWidth,
       int _filmHeight):
  m_screenWidth(_filmWidth),
  m_screenHeight(_filmHeight),
  m_aspectRatio((double)m_screenWidth / (double)m_screenHeight),
  m_fovMult(tan(_fov * M_PI/360))
{
  //generating a transformation matrix to transform from
  //camera space to world space
  //generate an orthonormal frame for the camera:
  ngl::Vec3 d = _lookAt - _pos;
  ngl::Vec3 r = _up.cross(d);
  ngl::Vec3 u = d.cross(r);
  d.normalize();
  r.normalize();
  u.normalize();
  //generate a matrix that can transform from points in
  //camera space to points in world space

  //matrix to allign roataions
  ngl::Mat4 rotate(r[0], u[0], d[0], 0,
                   r[1], u[1], d[1], 0,
                   r[2], u[2], d[2], 0,
                   0,    0,    0,    1);

  //matrix for position transformations
  ngl::Mat4 translate(1, 0, 0, _pos[0],
                      0, 1, 0, _pos[1],
                      0, 0, 1, _pos[2],
                      0, 0, 0,  1);
  //I store the roataion seperately because that is needed on its own
  //to roatate the direction vector of rays without translating them
  m_rotate = rotate;
  m_camToWorld = translate * rotate ;
}

void Camera::generateRay(double _x, double _y, Ray *_ray) const
{
  //init originposition
  ngl::Vec4 origin(0, 0, 0, 1);

  //convert pixel values to normalised device coordinates
  double xNDC = (_x + 0.5) / m_screenWidth;
  double yNDC = (_y + 0.5) / m_screenHeight;

  //convert from NDC to screen space
  double xScreen = -((xNDC * 2) - 1) * m_aspectRatio * m_fovMult;
  double yScreen = (1 - (yNDC * 2)) * m_fovMult;

  //set the direction for the ray
  ngl::Vec4 direction(xScreen,
                      yScreen,
                      1,
                      1);
  //transform origin and direction into world space
  origin = m_camToWorld * origin;
  direction = m_rotate * direction;

  //direction.normalize();
  //convert from ngl::Vec4 to ngl::Vec3
  ngl::Vec3 originOut;
  ngl::Vec3 directionOut;
  originOut.set(origin);
  directionOut.set(direction);

  //pass origin and direction to the ray
  _ray->m_direction = directionOut;
  _ray->m_origin = originOut;
  _ray->setInvDirection();
}
