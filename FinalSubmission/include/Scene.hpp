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
  void setSceneGeo(std::shared_ptr<Primative> _sceneGeo){m_sceneGeo = _sceneGeo;}
private:
  std::shared_ptr<Primative> m_sceneGeo;
  std::vector<Light> m_sceneLights;

};

#endif//__SCENE_HPP__
