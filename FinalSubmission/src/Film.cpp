#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include "Film.hpp"
#include "IsectData.hpp"

Film::Film(int _w, int _h):
  m_filmWidth(_w),
  m_filmHeight(_h),
  m_normals(_w * _h, ngl::Colour(1.0f, 1.0f, 1.0f, 1.0f)),
  m_depth(_w * _h, ngl::Colour(1.0f, 1.0f, 1.0f, 1.0f)),
  m_diffuse(_w * _h, ngl::Colour(1.0f, 1.0f, 1.0f, 1.0f))
{
}

void Film::setNormalPixle(int _x, int _y, ngl::Colour _c)
{
  m_normals[_x + m_filmWidth * _y] = _c;
}

void Film::setDepthPixel(int _x, int _y, ngl::Colour _c)
{
  m_depth[_x + m_filmWidth * _y] = _c;
}

void Film::setDiffusePixel(int _x, int _y, ngl::Colour _c){
  m_diffuse[_x + m_filmWidth * _y] = _c;
}


