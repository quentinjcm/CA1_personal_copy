#include  "Scene.hpp"

bool Scene::intersect(const Ray &_ray, IsectData *_intersection)
{
  return m_sceneGeo->intersect(_ray, _intersection);
}
