#ifndef __AGGREGATEPRIM_HPP__
#define __AGGREGATEPRIM_HPP__

#include <memory>
#include <vector>

#include "Primative.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"

class AggregatePrim: public Primative
{
public:
  void addPrimative(std::shared_ptr<Primative> _prim);
  bool intersect(const Ray &_ray, IsectData *_intersection);
private:
  std::vector<std::shared_ptr<Primative>> m_primatives;
};

#endif//__AGGREGATEPRIM_HPP__
