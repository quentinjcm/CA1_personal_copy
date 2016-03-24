#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "memory"
#include "vector"

#include "Primative.hpp"
#include "Light.hpp"

class Scene: public Primative
{
public:
  bool intersect(const Ray &_ray, IsectData *_intersection);
  //void setSceneGeo(std::shared_ptr<Primative> _sceneGeo){m_sceneGeo = _sceneGeo;}
  void addPrim(std::shared_ptr<Primative> _prim){ m_sceneGeo.push_back(_prim); }
  void addLight(Light _light){ m_sceneLights.push_back(_light); }
  std::vector<Light> m_sceneLights;
private:
  std::vector<std::shared_ptr<Primative>> m_sceneGeo;


};

#endif//__SCENE_HPP__
