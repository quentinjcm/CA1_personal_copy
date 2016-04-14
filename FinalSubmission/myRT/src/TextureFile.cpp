#include <string>
#include <iostream>
#include <cmath>
#include <QImage>
#include <QImageReader>
#include <SDL2/SDL.h>
#include "ngl/Colour.h"
#include "TextureFile.hpp"

TextureFile::TextureFile(std::string _fileName):
  m_fileName(_fileName)
{
}


bool TextureFile::loadImage()
{
  // loads an image file using qimage
  QImage image;
  if (m_fileName != "")
  {
    if (image.load(m_fileName.c_str()))
    {
      m_imgWidth = image.width();
      m_imgHeight = image.height();
      m_pixels.resize(m_imgHeight * m_imgWidth);
      QRgb colour;
      // runing through the pixels in the qimage
      for (int x = 0; x < m_imgWidth; x++)
      {
        for (int y = 0; y < m_imgHeight; y++)
        {
          // each pixel is converted to an ngl colour value and stored in m_pixels
          colour = image.pixel(x, y);
          ngl::Colour c((double)qRed(colour)/255.0,
                        (double)qGreen(colour)/255.0,
                        (double)qBlue(colour)/255.0,
                        (double)qAlpha(colour)/255.0);
          m_pixels[x + m_imgWidth * y] = c;
        }
      }
      return true;
    }
    else{
      std::cout << "image failed to load: " << m_fileName << std::endl;
    }
  }
  return false;
}

ngl::Colour TextureFile::getPixel(double _u, double _v)
{
  double dummy;
  // getting rid of any integer part of the uv coordinates
  //ensures uv values between 0 and 1;
  _u = modf(_u, &dummy);
  _v = modf(_v, &dummy);
  int x = _u * m_imgWidth;

  //using 1-v because uvs go from bottom to top but the image was read top to bottom
  int y = (1-_v) * m_imgHeight;
  return m_pixels[x + m_imgWidth * y];
}


