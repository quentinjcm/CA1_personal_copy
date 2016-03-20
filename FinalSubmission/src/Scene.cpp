#include  "Scene.hpp"

bool Scene::intersect(const Ray &_ray, IsectData *_intersection)
{
  bool hasIntersected = false;
  for (std::shared_ptr<Primative> &prim: m_sceneGeo){
    if (prim->intersect(_ray, _intersection)){
      hasIntersected = true;
    }
  }
  return hasIntersected;
}

