#ifndef __MESHES_HPP__
#define __MESHES_HPP__

#include <memory>

#include "TriangleMesh.hpp"

class Meshes
{
public:
  static std::shared_ptr<TriangleMesh> Sphere(int _precision, float _radius);
  static std::shared_ptr<TriangleMesh> Sphere2(int _stacks, int _slices, float _radius);
  static std::shared_ptr<TriangleMesh> Plane();
  static std::shared_ptr<TriangleMesh> Sphere3();

private:
  static std::shared_ptr<TriangleMesh> getMeshFromVD(std::vector<ngl::vertData> _source);
  static void setLimits( ngl::vertData *_data);
};

#endif//__MESHES_HPP__
