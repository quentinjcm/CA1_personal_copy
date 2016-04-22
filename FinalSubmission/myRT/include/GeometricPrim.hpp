#ifndef GEOMETRICPRIM_HPP__
#define GEOMETRICPRIM_HPP__

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
  GeometricPrim(std::shared_ptr<Primative> _mesh, std::shared_ptr<Material> _material);

  /// @brief overload of the primative intersection method
  /// @param [in] &_ray the ray being tested for intersection
  /// @param [in] *_intersection a data structure to hold information about the point of intersection
  /// @param [out] a boolean that returns true if the intersection is sucessfull;
  bool intersect(const Ray &_ray, IsectData *_intersection);

  /// @brief overload of the primative shadow intersection method
  /// @param [in] &_ray the ray being tested for intersection
  /// @param [out] a boolean that returns true if the intersection is sucessfull;
  bool sIntersect(const Ray &_ray);

  /// @brief fills two vectors up with points and normals for all the geometry in the scene, this will be
  /// used in the opengl viewport
  /// @param [in] *_points is a vector to be filled up with point positions
  /// @param [in] *_normals is a vector to be filled up with normal vectors
  void getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals);

private:
  /// @brief a shared pointer to the geometric mesh
  std::shared_ptr<Primative> m_mesh;

  /// @brief a shared pointer to the material
  std::shared_ptr<Material> m_material;
};

#endif  // end of GEOMETRICPRIM_HPP__
