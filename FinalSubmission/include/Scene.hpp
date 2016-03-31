#ifndef SCENE_HPP
#define SCENE_HPP

#include "memory"
#include "vector"

#include "Primative.hpp"
#include "Light.hpp"

class Scene: public Primative
{
public:
  bool intersect(const Ray &_ray, IsectData *_intersection);
  bool sIntersect(const Ray &_ray);
  //void setSceneGeo(std::shared_ptr<Primative> _sceneGeo){m_sceneGeo = _sceneGeo;}
  void addPrim(std::shared_ptr<Primative> _prim){ m_sceneGeo.push_back(_prim); }
  void addLight(Light _light){ m_sceneLights.push_back(_light); }
  std::vector<Light> m_sceneLights;
private:
  std::vector<std::shared_ptr<Primative>> m_sceneGeo;


};

#endif//__SCENE_HPP__
