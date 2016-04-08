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

bool GeometricPrim::sIntersect(const Ray &_ray)
{
  if (m_mesh->sIntersect(_ray)){
    return true;
  }
  return false;
}

void GeometricPrim::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  m_mesh->getGLData(_points, _normals);
}
