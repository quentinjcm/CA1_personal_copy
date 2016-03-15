#ifndef __FILM_HPP__
#define __FILM_HPP__

#include <vector>

#include <SDL2/SDL.h>

class Film
{
public:
  Film(int _w, int _h);
  void setPixle(int _x, int _y, int _r, int _g, int _b, int _a);
  void getPixel(int _x, int _y);
  int getFilmWidth(){ return m_filmWidth; }
  int getFilmHeight(){ return m_filmHeight; }
  void show();

private:
  int m_filmWidth;
  int m_filmHeight;
  SDL_Renderer *m_renderer;
  std::vector<SDL_Color> m_pixelArr;
  void init();
  void drawPixels();
  Uint8 clipColour(int n);
};





#endif//__FILM_HPP__
