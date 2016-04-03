#ifndef GEOMETRICPRIM_HPP
#define GEOMETRICPRIM_HPP

#include <memory>

#include "Primative.hpp"
#include "TriangleMesh.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"
#include "Material.hpp"

/// @file GeometricPrim.hpp
/// @brief File containng the GeometricPrim class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 26/03/2016

/// @class GeometricPrim
/// @brief the GrometricPrim class inherits from primative so that it
/// has the same intersection interface as the other primatives, the
/// scene and aggregate primatives. The GeometricPrim links a material
/// pointer with a triangular mesh pointer.
class GeometricPrim : public Primative
{
public:
  /// @brief ctor for the GeometricPrim that sets the pointers
  /// @param [in] _mesh the triangular mesh that the primative will hold
  /// @param [in] _material is the material that the primative will hold
  GeometricPrim(std::shared_ptr<TriangleMesh> _mesh, std::shared_ptr<Material> _material);

  /// @brief overload of the primative intersection method
  /// @param [in] &_ray the ray being tested for intersection
  /// @param [in] *_intersection a data structure to hold information about the point of intersection
  /// @param [out] a boolean that returns true if the intersection is sucessfull;
  bool intersect(const Ray &_ray, IsectData *_intersection);

  bool sIntersect(const Ray &_ray);

  void getGLData(std::vector<ngl::Vec3> _points, std::vector<ngl::Vec3> _normals);

private:
  /// @brief a shared pointer to the geometric mesh
  std::shared_ptr<TriangleMesh> m_mesh;

  /// @brief a shared pointer to the material
  std::shared_ptr<Material> m_material;
};

#endif//__GEOMETRICPRIM_HPP__
