#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <memory>
#include "ngl/Vec3.h"
#include "ngl/Colour.h"
#include "TextureFile.hpp"

/// @file Material.hpp
/// @brief File contaiing the Material class that holds data to do with materials in the scene
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 08/04/2016

/// @class Material
/// @brief The Material class defines a material that is appled to objects in the scene. It contains
/// the texture file and atributes that define how the geometry is shaded.
class Material
{
public:
  /// @brief ctor that takes in all of the information required to define a material
  /// @param [in] _colour is the default diffuse colour of the material, to be used if no texture file is found
  /// @param [in] _smoothness is the smootheness of the material used for phong shading
  /// @param [in] _IOR is the index of refraction, which defines how much light is reflected and refracted at different angles
  /// @param [in] _isTransparent is a bool that tells the renderer to send difracted rays through the object
  /// @param [in] _isReflective is a bool that tells the renderer to send reflected rays into the scene to get reflected colour
  /// @param [in] _texFile is a string that is the relative path to the image file that is the diffues texture for the material
  Material(ngl::Colour _colour, int _smoothness, double _IOR, bool _isTransparent, bool _isReflective, std::string _texFile);

  /// @brief returns the diffues colour at the given uv coordinates
  /// @param [in] _u is the u component of the texture coordinate
  /// @param [in] _v is the v component of the texture coordinate
  /// @param [out] the colour at the given texture coordinates
  ngl::Colour getDiffuseColour(double _u, double _v);

  /// @brief the default colour of the material
  ngl::Colour m_diffuseColour;

  /// @brief a flag to indicate that a texture file has been sucessfully loaded into the material
  bool m_hasTexture;

  /// @brief a pointer to the texture file
  std::shared_ptr<TextureFile> m_diffuseTex;

  /// @brief smoothness of the material
  int m_smoothness;

  /// @brief index of refraction for the material
  double m_ior;

  /// @brief flag to indicate if the material is transparent
  bool m_isTransparent;

  /// @brief flag to indicate if the material is reflective
  bool m_isReflective;
};

#endif//MATERIAL_HPP
