#include <memory>
#include <iostream>

#include <ngl/Colour.h>

#include "Material.hpp"
#include "TextureFile.hpp"


Material::Material(ngl::Colour _colour, int _smoothness, double _IOR, bool _isTransparent, bool _isReflective, std::string _texFileName):
  m_diffuseColour(_colour),
  m_hasTexture(false),
  m_smoothness(_smoothness),
  m_ior(_IOR),
  m_isTransparent(_isTransparent),
  m_isReflective(_isReflective)
{
  m_diffuseTex = std::make_shared<TextureFile>(_texFileName);
  m_diffuseTex->loadImage();
  if (m_diffuseTex->m_isLoaded){
    m_hasTexture = true;
  }
}

ngl::Colour Material::getDiffuseColour(double _u, double _v)
{
  if(m_hasTexture){
    return m_diffuseTex->getPixel(_u, _v);
  }
  else{
    return m_diffuseColour;
  }
}


