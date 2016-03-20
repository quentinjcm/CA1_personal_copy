#ifndef __MESHES_HPP__
#define __MESHES_HPP__

#include <memory>

#include "TriangleMesh.hpp"

class Meshes
{
public:
  static std::shared_ptr<TriangleMesh> Plane();
  static std::shared_ptr<TriangleMesh> scene1();
  static std::shared_ptr<TriangleMesh> sceneBox();
  static std::shared_ptr<TriangleMesh> SphereUV();
  static std::shared_ptr<TriangleMesh> Block();
  static std::shared_ptr<TriangleMesh> Torus();
  static std::shared_ptr<TriangleMesh> Bot();
};

#endif//__MESHES_HPP__
