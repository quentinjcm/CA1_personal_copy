#include <memory>
#include <vector>

#include "AggregatePrim.hpp"
#include "Primative.hpp"
#include "Ray.hpp"
#include "IsectData.hpp"

void AggregatePrim::addPrimative(std::shared_ptr<Primative> _prim)
{
  m_primatives.push_back(_prim);
}

bool AggregatePrim::intersect(const Ray &_ray, IsectData *_intersection)
{
  bool hasIntersected = false;
  for (std::shared_ptr<Primative> &prim: m_primatives){
    if (prim->intersect(_ray, _intersection)){
      hasIntersected = true;
    }
  }
  return hasIntersected;
}
