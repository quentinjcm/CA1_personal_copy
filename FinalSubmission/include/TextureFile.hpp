#ifndef TEXTUREFILE_HPP
#define TEXTUREFILE_HPP

#include <string>
#include <vector>

#include <ngl/Colour.h>

/// @file TextureFile.hpp
/// @brief File containing the TextureFile class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 27/03/2016

/// @class TextureFile
/// @brief used to load and store textures and get the colour of the
/// textures at specified uv coordinates
class TextureFile
{
public:
  /// @brief ctor that sets the file name of the texture
  /// @param [in] _fileName is a string that contains the file name of the texture to be loaded
  TextureFile(std::string _fileName);

  /// @brief loads the image and sets the isLoaded flag to true if sucessfull
  /// @param [out] a boolean that indicates that the texture file was loaded sucessfully
  bool loadImage();

  /// @brief gets the pixel value at the given uv texture coordinate
  /// @param [in] _u is the u value of the texture coordinate
  /// @param [in] _v is the v value of the texture coordinate
  /// @param [out] is the colour at the give texture coordinate
  ngl::Colour getPixel(double _u, double _v);
private:

  /// @brief vector of colour pixels that make up the texture image
  std::vector<ngl::Colour> m_pixels;

  /// @brief file name of the texture to load
  std::string m_fileName;

  /// @brief width of the image in pixels, set when the image is loaded
  int m_imgWidth;

  /// @brief height of the image in pixels, set when the image is loaded
  int m_imgHeight;
};

#endif//TEXTUREFILE_HPP
