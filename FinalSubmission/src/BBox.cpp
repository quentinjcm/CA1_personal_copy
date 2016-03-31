#include <iostream>
#include <limits>
#include <algorithm>

#include <ngl/Vec3.h>
#include <ngl/NGLStream.h>

#include "BBox.hpp"
#include "Ray.hpp"

BBox::BBox():
  m_pMin(0, 0, 0),
  m_pMax(0, 0, 0)
{
}

BBox::BBox(const ngl::Vec3 &_p):
  m_pMin(_p),
  m_pMax(_p)
{
}

BBox::BBox(const ngl::Vec3 &_p1, ngl::Vec3 &_p2):
  m_pMin(_p1),
  m_pMax(_p1)
{
  addPoint(_p2);
}

void BBox::addPoint( const ngl::Vec3 &_p)
{
  for (int i: {0, 1, 2}){
    //check all 3 coordinates to see if the new point has a lower value than m_pMin in any direction
    if (_p[i] < m_pMin[i]){
      m_pMin[i] = _p[i];
    }
    //check all 3 coordinates to see if the new point has a larger value than m_pMin in any direction
    else if (_p[i] >  m_pMax[i]){
      m_pMax[i] = _p[i];
    }
  }
}

void BBox::printData()
{
  std::cout << "Printing BBox\n";
  std::cout << "min: "<< m_pMin << "\nmax: " << m_pMax << std::endl;
}

bool BBox::intersect(const Ray &_ray)
{
  //using the slab method for bbox intersections,
  // an explanation can be found at: https://tavianator.com/fast-branchless-raybounding-box-intersections/
  //first two parametric values are set to theur numerical limits
  double tMin = std::numeric_limits<double>::min();
  double tMax = std::numeric_limits<double>::max();
  //it then runs through each of x, y and z and the ray is checked for intersections with each pair of faces
  for (int i: {0, 1, 2}){
    //finding the t value for each of the slabs
    double t1 = (m_pMin[i] - _ray.m_origin[i]) * _ray.m_invDirection[i];
    double t2 = (m_pMax[i] - _ray.m_origin[i]) * _ray.m_invDirection[i];
    //if the maximum value is greater than the minimum value then the ray intersects that particular slab
    tMin = std::max(tMin, std::min(t1, t2));
    tMax = std::min(tMax, std::max(t1, t2));
  }
  if (tMax >= tMin){
    return true;
  }
  return false;
}
