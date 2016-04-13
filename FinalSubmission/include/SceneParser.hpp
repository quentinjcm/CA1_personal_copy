#ifndef SCENEPARSER_HPP
#define SCENEPARSER_HPP

//stdlib includes
#include <string>
#include <memory>

//ngl includes
#include <ngl/Obj.h>
#include <ngl/Transformation.h>

//my includes
#include "Scene.hpp"
#include "Material.hpp"

/// @file SceneParser.hpp
/// @brief File containing the SceneParser class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 27/03/2016

/// @class SceneParser
/// @brief the Scene parser reads in scene files as .txts and translates them into an
/// objects to be placed in the scene. The class takes a pointer to its scene at constructio
/// instead of creating its own so that there is a potenial to have several files parsed to
/// the same scene object. For a guide on formatting scene files please see the readme. The
/// parser uses the boost spirit library to define the scene file syntax in EBFN. The parser
/// holds a pointer toa current material, which is passed to  each mesh as it is constructed.
/// see: https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_Form
class SceneParser
{
public:
  /// @brief ctor that sets the file name to parse and the scene to fill up with meshes
  /// @param [in] _fileName is a std string containing the file name as a path from the current directory
  /// @param [in] _scene is a shared pointer to the scene that the parser will place all of its object in
  SceneParser(std::string _fileName, std::shared_ptr<Scene> _scene);

  /// @brief main function that runs the parser
  void parseScene();

private:
  /// @brief a function defining the sphere gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parseSphere(const char *_begin);

  /// @brief a function defining the plane gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parsePlane(const char *_begin);

  /// @brief a function defining the obj gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parseObj(const char *_begin);

  /// @brief a function defining the material gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parseMat(const char *_begin);

  /// @brief a function defining the light gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parseLight(const char *_begin);

  /// @brief a function defining the translation gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parseTranslate(const char *_begin);

  /// @brief a function defining the rotation gramar as it appears in the scene file and how it is to be handled
  /// @param[in] *_begin is a pointer to the first element of the line being parsed
  void parseRotate(const char *_begin);

  /// @brief the current transformation that is applied to new objects as they are created
  ngl::Transformation m_currentTransform;

  /// @brief a pointer to the output scene
  std::shared_ptr<Scene> m_scene;

  /// @brief a pointer to the current material
  std::shared_ptr<Material> m_currentMat;

  /// @brief a string containing the file name of the scene file to parse
  std::string m_fileName;
};

#endif//SCENEPARSER_HPP
