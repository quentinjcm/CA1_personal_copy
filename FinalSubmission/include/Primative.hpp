#ifndef PRIMATIVE_HPP
#define PRIMATIVE_HPP

#include "Ray.hpp"
#include "IsectData.hpp"

class Primative
{
public:
  virtual bool intersect(const Ray &_ray, IsectData *_intersection);
  virtual bool sIntersect(const Ray &_ray);
  virtual void getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals);
private:
};


#endif//__PRIMATIVE_HPP__
