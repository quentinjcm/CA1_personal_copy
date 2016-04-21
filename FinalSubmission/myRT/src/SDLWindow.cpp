#include <iostream>
#include <ctime>
#include <SDL2/SDL.h>
#include "SDLWindow.hpp"
#include "Film.hpp"


SDLWindow::SDLWindow(Film *_film):
  m_windowWidth(_film->getFilmWidth()),
  m_windowHeight(_film->getFilmHeight()),
  m_pixelsToDraw(_film->getPixelArr()),
  m_film(_film)
{
  // initialising sdl
  init();
}

void SDLWindow::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Could not init sdl" << SDL_GetError() << std::endl;
    m_isInitialised = false;
  }
  else
  {
    m_isInitialised = true;
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
  while(go)
  {
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT: go = false; break;
      case SDL_KEYUP: keyPress(&event); break;
    }
    if (!m_film->getImageComplete())
    {
      updateSurface();
    }
    SDL_UpdateWindowSurface( m_window );
  }
  SDL_FreeSurface(m_surface);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void SDLWindow::keyPress(SDL_Event *_event)
{
  // saves an image when s is pressed
  SDL_Keycode keyPressed = _event->key.keysym.sym;
  switch (keyPressed)
  {
    case SDLK_s: saveSurfaceToBMP(); break;
    case SDLK_u: updateSurface(); break;
  }
}

void SDLWindow::updateSurface()
{
  // gets the renderers surfaces as a pixel array
  Uint32 *pixels = (Uint32 *)m_surface->pixels;
  for (int x = 0; x < m_windowWidth; x++)
  {
    for (int y = 0; y < m_windowHeight; y++)
    {
      // converts rendered pixel to a uint 32 for sdl to draw
      ngl::Colour c = (*m_pixelsToDraw)[x + m_windowWidth * y];
      Uint32 out = SDL_MapRGBA(m_surface->format,
                               (Uint8)(c.m_r*255),
                               (Uint8)(c.m_g*255),
                               (Uint8)(c.m_b*255),
                               (Uint8)(c.m_a*255));
      //sets the surface pixel to the converted one
      pixels[x + m_windowWidth * y] = out;
    }
  }
}


void SDLWindow::saveSurfaceToBMP()
{
  if(!m_hasSaved)
  {
    // setting up the file name
    std::string fName("saves/render_");
    time_t current_time = time(NULL);
    fName += ctime(&current_time);
    fName += ".bmp";
    // saving the renderes surface using the filename
    SDL_SaveBMP(m_surface, fName.c_str());
    std::cout << "Image saved: " << fName << std::endl;
    m_hasSaved = true;
  }
}
