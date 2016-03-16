#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>

class Light
{
public:
  ngl::Vec3 m_pos;
  SDL_Color m_colour;
  float m_intensity;
};

#endif//__LIGHT_HPP__
