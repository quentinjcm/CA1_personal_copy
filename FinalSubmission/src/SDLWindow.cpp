#include <iostream>

#include "SDLWindow.hpp"
#include "Film.hpp"


SDLWindow::SDLWindow(Film *_film):
  m_windowWidth(_film->getFilmWidth()),
  m_windowHeight(_film->getFilmHeight()),
  m_film(_film),
  m_pixelsToDraw(m_film->getPixelArr())
{
  init();
}

void SDLWindow::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr << "Could not init sdl" << SDL_GetError() << std::endl;
  }
}

void SDLWindow::run()
{
  m_window = SDL_CreateWindow("Film",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              m_windowWidth,
                              m_windowHeight,
                              SDL_WINDOW_SHOWN);
  m_surface = SDL_GetWindowSurface(m_window);
  bool go = true;
  updateSurface();
  while(go){
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch(event.type){
      case SDL_QUIT: go = false; break;
      case SDL_KEYDOWN: keyPress(&event); break;
    }
    SDL_UpdateWindowSurface( m_window );
  }
  SDL_FreeSurface(m_surface);
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void SDLWindow::keyPress(SDL_Event *_event)
{
/*
  SDL_Keycode keyPressed = _event->key.keysym.sym;
  switch (keyPressed) {
    case SDLK_1: m_pixelsToDraw = m_film->getDiffuseArr(); break;
    case SDLK_2: m_pixelsToDraw = m_film->getNormalArr(); break;
    case SDLK_3: m_pixelsToDraw = m_film->getDepthArr(); break;
  }
  updateSurface();
  */
}

void SDLWindow::updateSurface()
{
  for (int x = 0; x < m_windowWidth; x++){
    for (int y = 0; y < m_windowHeight; y++){
      ngl::Colour c = (*m_pixelsToDraw)[x + m_windowWidth * y];
      Uint32 out = SDL_MapRGBA(m_surface->format,
                               (Uint8)(c.m_r*255),
                               (Uint8)(c.m_g*255),
                               (Uint8)(c.m_b*255),
                               (Uint8)(c.m_a*255));
      Uint32 *pixels = (Uint32 *)m_surface->pixels;
      pixels[x + m_windowWidth * y] = out;
    }
  }
}
