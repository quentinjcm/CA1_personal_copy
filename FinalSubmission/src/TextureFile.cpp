#include <string>
#include <iostream>

#include <QImage>

#include <SDL2/SDL.h>

#include "TextureFile.hpp"

TextureFile::TextureFile(std::string _fileName):
  m_fileName(_fileName),
  m_isLoaded(false)
{
}


void TextureFile::loadImage()
{
  QImage image;
  m_isLoaded = image.load(m_fileName.c_str());
  if (m_isLoaded){
    m_imgWidth = image.width();
    m_imgHeight = image.height();
    m_pixels.resize(m_imgHeight * m_imgWidth);
    QRgb colour;
    for (int x = 0; x < m_imgWidth; x++){
      for (int y = 0; y < m_imgHeight; y++){
        colour = image.pixel(x, y);
        SDL_Color sdlColour{(Uint8)qRed(colour),
                            (Uint8)qGreen(colour),
                            (Uint8)qBlue(colour),
                            (Uint8)qAlpha(colour)};
        m_pixels[x + m_imgWidth * y] = sdlColour;
      }
    }
  }
}

SDL_Color TextureFile::getPixel(float _u, float _v)
{
  int x = _u * m_imgWidth;
  int y = _v * m_imgHeight;
  return m_pixels[x + m_imgWidth * y];
}


