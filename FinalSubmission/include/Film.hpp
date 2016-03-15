#ifndef __FILM_HPP__
#define __FILM_HPP__

#include <vector>

#include <ngl/Vec3.h>

#include <SDL2/SDL.h>

class Film
{
public:
  Film(int _w, int _h);
  void setNormalPixle(int _x, int _y, ngl::Vec3 _normal);
  void setDepthPixel(int _x, int _y, float _depth);
  void setDiffusePixel(int _x, int _y, SDL_Color _colour);
  int getFilmWidth(){ return m_filmWidth; }
  int getFilmHeight(){ return m_filmHeight; }
  std::vector<SDL_Color>* getDiffuseArr(){ return &m_diffuse; }
  std::vector<SDL_Color>* getNormalArr(){ return &m_normals; }
  std::vector<SDL_Color>* getDepthArr(){ return &m_depth; }

private:
  int m_filmWidth;
  int m_filmHeight;
  std::vector<SDL_Color> m_normals;
  std::vector<SDL_Color> m_depth;
  std::vector<SDL_Color> m_diffuse;
  Uint8 clipColour(int n);
};





#endif//__FILM_HPP__
