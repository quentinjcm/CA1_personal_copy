#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include "TextureFile.hpp"

class Material
{
public:
  Material();
  Material(ngl::Colour _colour, int _smoothness, double _IOR, bool _isTransparent, bool _isReflective, std::string _texFile);
  Material(std::string _texFileName);

  ngl::Colour getDiffuseColour(double _u, double _v);
  ngl::Colour m_diffuseColour;
  bool m_hasTexture;
  std::shared_ptr<TextureFile> m_diffuseTex;
  int m_smoothness;
  double m_f0;
  bool m_isTransparent;
  bool m_isReflective;
};

#endif//__MATERIAL_HPP__
