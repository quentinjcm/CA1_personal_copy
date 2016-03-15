#include <iostream>

#include <SDL2/SDL.h>

#include "Film.hpp"

Film::Film(int _w, int _h):
  m_filmWidth(_w),
  m_filmHeight(_h),
  m_pixelArr(_w * _h, SDL_Color{255, 255, 255, 255})
{
  std::cout << "film created: " << _w << ", " << _h << std::endl;
  init();
}

void Film::setPixle(int _x, int _y, int _r, int _g, int _b, int _a)
{
  SDL_Color temp{clipColour(_r),
                 clipColour(_g),
                 clipColour(_b),
                 clipColour(_a)};
  m_pixelArr[_x + m_filmWidth * _y] = temp;
}

void Film::getPixel(int _x, int _y)
{
  Uint8 r = m_pixelArr[_x + m_filmWidth * _y].r;
  Uint8 g = m_pixelArr[_x + m_filmWidth * _y].g;
  Uint8 b = m_pixelArr[_x + m_filmWidth * _y].b;
  Uint8 a = m_pixelArr[_x + m_filmWidth * _y].a;

  std::cout << "colour is " << unsigned(r) << " " << unsigned(g) << " " << unsigned(b) << " " << unsigned(a) << std::endl;
}

void Film::show()
{
  SDL_Window *window = SDL_CreateWindow("Film",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        m_filmWidth,
                                        m_filmHeight,
                                        SDL_WINDOW_SHOWN);
  m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  bool go = true;
  while(go){
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT: go = false; break;
    }
    drawPixels();
    SDL_RenderPresent(m_renderer);
  }
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(window);
}

void Film::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr << "Could not init sdl" << SDL_GetError() << std::endl;
  }
}

void Film::drawPixels()
{
  for (int x = 0; x < m_filmWidth; x++){
    for (int y = 0; y < m_filmHeight; y++){
      SDL_SetRenderDrawColor(m_renderer,
                             m_pixelArr[x + m_filmWidth * y].r,
                             m_pixelArr[x + m_filmWidth * y].g,
                             m_pixelArr[x + m_filmWidth * y].b,
                             m_pixelArr[x + m_filmWidth * y].a);
      SDL_RenderDrawPoint(m_renderer, x, y);
    }
  }
}

Uint8 Film::clipColour(int n) {
  return (Uint8)std::max(0, std::min(n, 255));
}

