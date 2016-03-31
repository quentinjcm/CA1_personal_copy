#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

class Light
{
public:
  Light() = default;
  Light(ngl::Vec3 _pos, ngl::Colour _colour, double _intensity);
  ngl::Vec3 m_pos;
  ngl::Colour m_colour;
  double m_intensity;
};

#endif//__LIGHT_HPP__
