#ifndef __GEOMETRICPRIM_HPP__
#define __GEOMETRICPRIM_HPP__

#include <memory>

#include "Primative.hpp"
#include "TriangleMesh.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"
#include "Material.hpp"

class GeometricPrim : public Primative
{
public:
  GeometricPrim(std::shared_ptr<TriangleMesh> _mesh, std::shared_ptr<Material> _material);
  bool intersect(const Ray &_ray, IsectData *_intersection);

private:
  std::shared_ptr<TriangleMesh> m_mesh;
  std::shared_ptr<Material> m_material;
};

#endif//__GEOMETRICPRIM_HPP__
