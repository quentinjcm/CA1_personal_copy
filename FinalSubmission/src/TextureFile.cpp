#include <string>
#include <iostream>

#include <QImage>
#include <QImageReader>

#include <SDL2/SDL.h>

#include <ngl/Colour.h>

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
        ngl::Colour c((double)qRed(colour)/255.0,
                      (double)qGreen(colour)/255.0,
                      (double)qBlue(colour)/255.0,
                      (double)qAlpha(colour)/255.0);
        m_pixels[x + m_imgWidth * y] = c;
      }
    }
  }
  else{
    std::cout << "image failed to load" << std::endl;
    m_isLoaded = false;
  }
}

ngl::Colour TextureFile::getPixel(double _u, double _v)
{
  int x = _u * m_imgWidth;
  int y = (1-_v) * m_imgHeight;
  return m_pixels[x + m_imgWidth * y];
}


