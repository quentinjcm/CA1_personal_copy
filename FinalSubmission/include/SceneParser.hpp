#ifndef __SCENEPARSER_HPP__
#define __SCENEPARSER_HPP__

#include <string>
#include <memory>

#include <ngl/Obj.h>

#include "Scene.hpp"
#include "Material.hpp"

class SceneParser
{
public:
  SceneParser(std::string _fileName, std::shared_ptr<Scene> _scene);
  void parseScene();
  void parseSphere(const char *_begin);
  void parsePlane(const char *_begin);
  void parseObj(const char *_begin);
  void parseMat(const char *_begin);
  void parseLight(const char *_begin);
private:
  std::shared_ptr<Scene> m_scene;
  std::shared_ptr<Material> m_currentMat;
  std::string m_fileName;
};

#endif//__SCENEPARSER_HPP__
