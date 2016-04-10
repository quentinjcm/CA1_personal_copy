#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

/// @file Light.hpp
/// @brief File contaiing the Light class that holds data to do with lights in the scene
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 08/04/2016

/// @struct Light
/// @brief The light class holds data that defines lights in the scene,
/// A light is a combination of a position, colour and intensity
struct Light
{
  /// @brief ctor that takes in all of the data that defines a light
  /// @param [in] _pos is the position of the light in world space
  /// @param [in] _colour is the rgb colour of the light
  /// @param [in] _intensity is the intensity of the light
  Light(ngl::Vec3 _pos, ngl::Colour _colour, double _intensity):
    m_pos(_pos),
    m_colour(_colour),
    m_intensity(_intensity){}

  /// @brief a vec3 that holds the position of the light
  ngl::Vec3 m_pos;

  /// @brief a colour that holds the rgb colour value of the light
  ngl::Colour m_colour;

  /// @brief the intensity of the light
  double m_intensity;
};

#endif//LIGHT_HPP
