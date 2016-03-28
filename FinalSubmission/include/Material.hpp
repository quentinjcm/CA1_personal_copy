#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

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
  Material(ngl::Colour _colour, int _smoothness, float _IOR, bool _isTransparent, bool _isReflective, std::string _texFile);
  Material(std::string _texFileName);

  ngl::Colour getDiffuseColour(float _u, float _v);
  ngl::Colour m_diffuseColour;
  bool m_hasTexture;
  std::shared_ptr<TextureFile> m_diffuseTex;
  int m_smoothness;
  float m_f0;
  bool m_isTransparent;
  bool m_isReflective;
};

#endif//__MATERIAL_HPP__
