#include <iostream>

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>

#include "Film.hpp"

Film::Film(int _w, int _h):
  m_filmWidth(_w),
  m_filmHeight(_h),
  m_depth(_w * _h, SDL_Color{255, 255, 255, 255}),
  m_normals(_w * _h, SDL_Color{255, 255, 255, 255}),
  m_diffuse(_w * _h, SDL_Color{255, 255, 255, 255})
{
}

void Film::setNormalPixle(int _x, int _y, ngl::Vec3 _normal)
{
  SDL_Color temp{clipColour(_normal[0] * 255),
                 clipColour(_normal[1] * 255),
                 clipColour(_normal[2] * 255),
                 255};
  m_normals[_x + m_filmWidth * _y] = temp;
}

void Film::setDepthPixel(int _x, int _y, float _depth)
{
  SDL_Color temp{clipColour(_depth),
                 clipColour(_depth),
                 clipColour(_depth),
                 255};
  m_depth[_x + m_filmWidth * _y] = temp;
}

void Film::setDiffusePixel(int _x, int _y, SDL_Color _colour){
  m_diffuse[_x + m_filmWidth * _y] = _colour;
}


Uint8 Film::clipColour(int n) {
  return (Uint8)std::max(0, std::min(n, 255));
}

