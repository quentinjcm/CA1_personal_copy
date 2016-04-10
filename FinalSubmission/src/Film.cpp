#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include "Film.hpp"
#include "IsectData.hpp"

/// @file Film.cpp
/// @brief implementation file for the Film class

Film::Film(int _w, int _h):
  m_filmWidth(_w),
  m_filmHeight(_h),
  m_pixels(_w * _h, ngl::Colour(1.0f, 0.0f, 0.0f, 1.0f))
{
}

void Film::setPixel(int _x, int _y, ngl::Colour _c)
{
  m_pixels[_x + m_filmWidth * _y] = _c;
}


