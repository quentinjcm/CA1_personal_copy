#ifndef __TEXTUREFILE_HPP__
#define __TEXTUREFILE_HPP__

#include <string>
#include <vector>

#include <SDL2/SDL.h>


class TextureFile
{
public:
  TextureFile(std::string _fileName);
  void loadImage();
  SDL_Color getPixel(float _u, float _v);
  std::string m_fileName;
  std::vector<SDL_Color> m_pixels;
  bool m_isLoaded;
  int m_imgWidth;
  int m_imgHeight;
};

#endif//__TEXTUREFILE_HPP__
