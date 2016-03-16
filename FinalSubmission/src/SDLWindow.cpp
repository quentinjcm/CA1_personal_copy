#include <iostream>

#include "SDLWindow.hpp"
#include "Film.hpp"


SDLWindow::SDLWindow(Film *_film):
  m_windowWidth(_film->getFilmWidth()),
  m_windowHeight(_film->getFilmHeight()),
  m_film(_film),
  m_pixelsToDraw(m_film->getDiffuseArr())
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
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  bool go = true;
  while(go){
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch(event.type){
      case SDL_QUIT: go = false; break;
      case SDL_KEYDOWN: keyPress(&event); break;
    }
    drawPixels();
    SDL_RenderPresent(m_renderer);
  }
}

void SDLWindow::drawPixels()
{
  for (int x = 0; x < m_windowWidth ; x++){
    for (int y = 0; y < m_windowHeight; y++){
      SDL_Color colour = (*m_pixelsToDraw)[x + m_windowWidth * y];
      SDL_SetRenderDrawColor(m_renderer,
                             colour.r,
                             colour.g,
                             colour.b,
                             colour.a);
      SDL_RenderDrawPoint(m_renderer, x, y);
    }
  }
}

void SDLWindow::keyPress(SDL_Event *_event)
{

  SDL_Keycode keyPressed = _event->key.keysym.sym;
  switch (keyPressed) {
    case SDLK_1: m_pixelsToDraw = m_film->getDiffuseArr(); break;
    case SDLK_2: m_pixelsToDraw = m_film->getNormalArr(); break;
    case SDLK_3: m_pixelsToDraw = m_film->getDepthArr(); break;
  }
}
