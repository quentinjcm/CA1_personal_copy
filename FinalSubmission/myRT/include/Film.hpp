#ifndef FILM_HPP__
#define FILM_HPP__

#include <vector>
#include <memory>
#include "ngl/Vec3.h"
#include "ngl/Colour.h"
#include "IsectData.hpp"

/// @file Film.hpp
/// @brief File contaiing the Film class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 27/03/2016

/// @class Film
/// @brief The Film class holds pixel arrayd for the different render layers
class Film
{
public:
  /// @brief ctor that sets the size of the pixel vectors
  /// @param [in] _w is the width of the film
  /// @param [in] _h is the height of the film
  Film(int _w, int _h);

  /// @brief sets a pixel in the colour vector
  /// @param [in] _x is the x coordinate of the pixel in screen space
  /// @param [in] _y is the y coordinate of the pixel in screen space
  /// @param [in] _c is the colour to set the target pixel
  void setPixel(int _x, int _y, ngl::Colour _c);

  /// @brief returns the width of the film
  /// @param [out] returns the integer width of the film in pixels
  int getFilmWidth(){ return m_filmWidth; }

  /// @brief returns the height of the film
  /// @param [out] returns the integer height of the film in pixels
  int getFilmHeight(){ return m_filmHeight; }

  /// @breif getter for the colour pixel vector
  /// @param [out] returns a pointer to the vector that holds the colour pixel values that are set by the renderer
  std::vector<ngl::Colour>* getPixelArr(){ return &m_pixels; }

  bool getImageComplete(){ return m_imageComplete; }

  void setImageComplete(bool _status){ m_imageComplete = _status; }

private:
  /// @brief width of the film in pixels
  int m_filmWidth;

  /// @brief height of the film in pixels
  int m_filmHeight;

  /// @brief vector of pixels
  std::vector<ngl::Colour> m_pixels;

  bool m_imageComplete = false;
};





#endif  // end of FILM_HPP__
