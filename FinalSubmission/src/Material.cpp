#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

#include <ngl/Colour.h>

#include "Material.hpp"
#include "TextureFile.hpp"

Material::Material():
  m_hasTexture(false)
{
}

Material::Material(ngl::Colour _colour, int _smoothness, float _IOR, std::string _texFileName):
  m_hasTexture(false),
  m_smoothness(_smoothness),
  m_f0(_IOR)
{
  m_diffuseTex = std::make_shared<TextureFile>(_texFileName);
  m_diffuseTex->loadImage();
  if (m_diffuseTex->m_isLoaded){
    m_hasTexture = true;
  }
}

Material::Material(std::string _texFileName):
  m_hasTexture(false)
{
  m_diffuseTex = std::make_shared<TextureFile>(_texFileName);
  m_diffuseTex->loadImage();
  if (m_diffuseTex->m_isLoaded){
    m_hasTexture = true;
  }
}

ngl::Colour Material::getDiffuseColour(float _u, float _v)
{
  if(m_hasTexture){
    return m_diffuseTex->getPixel(_u, _v);
  }
  else{
    return m_diffuseColour;
  }
}


