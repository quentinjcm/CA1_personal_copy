#ifndef TEXTUREFILE_HPP
#define TEXTUREFILE_HPP

#include <string>
#include <vector>

#include <ngl/Colour.h>

class TextureFile
{
public:
  TextureFile(std::string _fileName);
  void loadImage();
  ngl::Colour getPixel(double _u, double _v);
  std::string m_fileName;
  std::vector<ngl::Colour> m_pixels;
  bool m_isLoaded;
  int m_imgWidth;
  int m_imgHeight;
};

#endif//__TEXTUREFILE_HPP__
