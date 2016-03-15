#include <memory>

#include "GeometricPrim.hpp"
#include "TriangleMesh.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"

GeometricPrim::GeometricPrim(std::shared_ptr<TriangleMesh> _mesh):
  m_mesh(_mesh)
{
}

bool GeometricPrim::intersect(const Ray &_ray, IsectData *_intersection)
{
  return m_mesh->intersect(_ray, _intersection);
}
