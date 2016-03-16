#ifndef __SDLWINDOW_HPP__
#define __SDLWINDOW_HPP__

#include <vector>

#include <SDL2/SDL.h>

#include "Film.hpp"

class SDLWindow
{
public:
  SDLWindow(Film *_film);
  void init();
  void run();
  void keyPress(SDL_Event *_event);
  void drawPixels();

private:
  int m_windowWidth;
  int m_windowHeight;
  Film *m_film;
  SDL_Renderer *m_renderer;
  SDL_Window *m_window;
  std::vector<SDL_Color> *m_pixelsToDraw;

};

#endif//__SDLWINDOW_HPP__
