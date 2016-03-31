#include <SDL2/SDL.h>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include "Light.hpp"

Light::Light(ngl::Vec3 _pos, ngl::Colour _colour, double _intensity):
  m_pos(_pos),
  m_colour(_colour),
  m_intensity(_intensity)
{
}
