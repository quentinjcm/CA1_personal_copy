#ifndef __MESHES_HPP__
#define __MESHES_HPP__

#include <memory>

#include "TriangleMesh.hpp"

class Meshes
{
public:
  static std::shared_ptr<TriangleMesh> scene1();
  static std::shared_ptr<TriangleMesh> sceneBox();
  static std::shared_ptr<TriangleMesh> Sphere();
  static std::shared_ptr<TriangleMesh> Block();
  static std::shared_ptr<TriangleMesh> Torus();
};

#endif//__MESHES_HPP__
