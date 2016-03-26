#include <memory>

#include "GeometricPrim.hpp"

GeometricPrim::GeometricPrim(std::shared_ptr<TriangleMesh> _mesh, std::shared_ptr<Material> _material):
  m_mesh(_mesh),
  m_material(_material)
{
}

bool GeometricPrim::intersect(const Ray &_ray, IsectData *_intersection)
{
  if (m_mesh->intersect(_ray, _intersection)){
    _intersection->m_material = m_material;
    return true;
  }
  return false;
}
