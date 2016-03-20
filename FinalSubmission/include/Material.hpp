#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include <ngl/Vec3.h>

#include "TextureFile.hpp"

class Material
{
public:
  Material();
  Material(std::string _texFileName);
  SDL_Color getDiffuseColour(float _u, float _v);
  SDL_Color m_diffuseColour;
  bool m_hasTexture;
  std::shared_ptr<TextureFile> m_diffuseTex;
};

#endif//__MATERIAL_HPP__
