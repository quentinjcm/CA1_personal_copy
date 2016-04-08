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

bool Scene::sIntersect(const Ray &_ray)
{
  for (std::shared_ptr<Primative> &prim: m_sceneGeo){
    if (prim->sIntersect(_ray)){
      return true;
    }
  }
  return false;
}

void Scene::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  for (std::shared_ptr<Primative> prim: m_sceneGeo){
    prim->getGLData(_points, _normals);
  }
}

