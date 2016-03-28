#ifndef __FILM_HPP__
#define __FILM_HPP__

// stdlib includes
#include <vector>
#include <memory>

//ngl includes
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

//my includes
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

  /// @brief sets a pixel in the normal vector
  /// @param [in] _x is the x coordinate of the pixel in screen space
  /// @param [in] _y is the y coordinate of the pixel in screen space
  /// @param [in] _c is the colour to set the target pixel
  void setNormalPixle(int _x, int _y, ngl::Colour _c);

  /// @brief sets a pixel in the depth vector
  /// @param [in] _x is the x coordinate of the pixel in screen space
  /// @param [in] _y is the y coordinate of the pixel in screen space
  /// @param [in] _c is the colour to set the target pixel
  void setDepthPixel(int _x, int _y, ngl::Colour _c);

  /// @brief sets a pixel in the colour vector
  /// @param [in] _x is the x coordinate of the pixel in screen space
  /// @param [in] _y is the y coordinate of the pixel in screen space
  /// @param [in] _c is the colour to set the target pixel
  void setDiffusePixel(int _x, int _y, ngl::Colour _c);

  /// @brief returns the width of the film
  /// @param [out] returns the integer width of the film in pixels
  int getFilmWidth(){ return m_filmWidth; }

  /// @brief returns the height of the film
  /// @param [out] returns the integer height of the film in pixels
  int getFilmHeight(){ return m_filmHeight; }

  /// @breif getter for the colour pixel vector
  /// @param [out] returns a pointer to the vector that holds the colour pixel values that are set by the renderer
  std::vector<ngl::Colour>* getDiffuseArr(){ return &m_diffuse; }

  /// @breif getter for the normal pixel vector
  /// @param [out] returns a pointer to the vector that holds the normal pixel values that are set by the renderer
  std::vector<ngl::Colour>* getNormalArr(){ return &m_normals; }

  /// @breif getter for the depth pixel vector
  /// @param [out] returns a pointer to the vector that holds the depth pixel values that are set by the renderer
  std::vector<ngl::Colour>* getDepthArr(){ return &m_depth; }

private:
  /// @brief width of the film in pixels
  int m_filmWidth;

  /// @brief height of the film in pixels
  int m_filmHeight;

  /// @brief vector of normal pixels
  std::vector<ngl::Colour> m_normals;

  /// @brief vector of depth pixels
  std::vector<ngl::Colour> m_depth;

  /// @brief vector of colour pixels
  std::vector<ngl::Colour> m_diffuse;
};





#endif//__FILM_HPP__
