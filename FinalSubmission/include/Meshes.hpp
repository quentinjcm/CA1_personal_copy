#ifndef __MESHES_HPP__
#define __MESHES_HPP__

#include <memory>

#include <ngl/Vec3.h>

#include "TriangleMesh.hpp"

class Meshes
{
public:
  static std::shared_ptr<TriangleMesh> pPlane(float _width, float _height);
  static std::shared_ptr<TriangleMesh> pSphere(float _r, int _sd);
private:
  static ngl::Vec3 circularToCartesian(float _theta, float _phi);
};

#endif//__MESHES_HPP__
