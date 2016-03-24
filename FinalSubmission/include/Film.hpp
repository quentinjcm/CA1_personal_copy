#ifndef __FILM_HPP__
#define __FILM_HPP__

#include <vector>
#include <memory>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include <SDL2/SDL.h>

#include "IsectData.hpp"

class Film
{
public:
  Film(int _w, int _h);
  void setNormalPixle(int _x, int _y, ngl::Colour _c);
  void setDepthPixel(int _x, int _y, ngl::Colour _c);
  void setDiffusePixel(int _x, int _y, ngl::Colour _c);
  int getFilmWidth(){ return m_filmWidth; }
  int getFilmHeight(){ return m_filmHeight; }
  std::vector<ngl::Colour>* getDiffuseArr(){ return &m_diffuse; }
  std::vector<ngl::Colour>* getNormalArr(){ return &m_normals; }
  std::vector<ngl::Colour>* getDepthArr(){ return &m_depth; }

private:
  int m_filmWidth;
  int m_filmHeight;
  std::vector<ngl::Colour> m_normals;
  std::vector<ngl::Colour> m_depth;
  std::vector<ngl::Colour> m_diffuse;
  Uint8 clipColour(int n);
};





#endif//__FILM_HPP__
