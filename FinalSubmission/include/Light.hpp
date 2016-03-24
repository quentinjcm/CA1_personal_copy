#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

class Light
{
public:
  Light() = default;
  Light(ngl::Vec3 _pos, ngl::Colour _colour, float _intensity);
  ngl::Vec3 m_pos;
  ngl::Colour m_colour;
  float m_intensity;
};

#endif//__LIGHT_HPP
