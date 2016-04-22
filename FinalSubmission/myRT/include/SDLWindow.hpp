#ifndef SDLWINDOW_HPP__
#define SDLWINDOW_HPP__

#include <vector>
#include <SDL2/SDL.h>
#include "ngl/Colour.h"
#include "Film.hpp"

/// @file SDLWindow.hpp
/// @brief File containing the SDLWindow class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 27/03/2016

/// @class SDLWindow
/// @brief used to display the final rendered image to the screen
class SDLWindow
{
public:
  /// @brief ctor that takes the film that will hold the data to be drawn to the scren
  /// @param [in] *_film is the film that will hold the data to be drawn
  SDLWindow(Film *_film);

  /// @brief initiliser that sets up sdl
  void init();

  /// @brief sets up the window and runs the main rendering loop
  void run();

  /// @brief function called when there is a keypress
  /// @param [in] *_event an sdl event containing the data on the keypress
  void keyPress(SDL_Event *_event);

  /// @brief updates the surface
  void updateSurface();

private:
  /// @brief saves the render as a bmp image
  void saveSurfaceToBMP();

  /// @brief the width of the sdl window
  int m_windowWidth;

  /// @brief the height of the sdl window
  int m_windowHeight;

  /// @brief the window that will be drawn into
  SDL_Window *m_window;

  /// @brief an array of pixels to draw to the screen
  std::vector<ngl::Colour> *m_pixelsToDraw;

  /// @brief the surface that the pixels are copied too for drawing to the window
  SDL_Surface *m_surface;

  /// @brief a bool that incicated if sdl was sucessfully initialised
  /// the window wont run if initilaisation failed
  bool m_isInitialised = false;

  /// @brief flag to indicate that the image has been saved
  bool m_hasSaved;

  /// @brief pointer to the film that
  Film *m_film;
};

#endif // end of SDLWINDOW_HPP__
