#include <memory>
#include "GeometricPrim.hpp"

/// @file GeometricPrim.cpp
/// @brief implementation file for the GeometricPrim class

GeometricPrim::GeometricPrim(std::shared_ptr<Primative> _mesh, std::shared_ptr<Material> _material):
  m_mesh(_mesh),
  m_material(_material)
{
}

bool GeometricPrim::intersect(const Ray &_ray, IsectData *_intersection)
{
  if (m_mesh->intersect(_ray, _intersection))
  {
    // passing the primatives material to the intersection data structure to go back to the renderer
    _intersection->m_material = m_material;
    return true;
  }
  return false;
}

bool GeometricPrim::sIntersect(const Ray &_ray)
{
  if (m_mesh->sIntersect(_ray))
  {
    return true;
  }
  return false;
}

void GeometricPrim::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  //unused function for getting gl data
  m_mesh->getGLData(_points, _normals);
}
