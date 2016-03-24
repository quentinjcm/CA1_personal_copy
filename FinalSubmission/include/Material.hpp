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
  Material(std::string _texFileName);
  ngl::Colour getDiffuseColour(float _u, float _v);
  ngl::Colour m_diffuseColour;
  bool m_hasTexture;
  std::shared_ptr<TextureFile> m_diffuseTex;
  int m_smoothness;
  float m_f0;
};

#endif//__MATERIAL_HPP__
