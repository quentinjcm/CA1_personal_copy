#include <iostream>
#include <vector>

#include <ngl/Vec3.h>

#include "TriangleMesh.hpp"
#include "Triangle.hpp"
#include "Ray.hpp"
#include "BBox.hpp"

///@file TriangleMesh.cpp
///@brief Implementation file for the TriangleMesh class

bool TriangleMesh::intersect(const Ray &_ray, IsectData *_intersection)
{
  if (intersectBBox(_ray)){
    return intersectMesh(_ray, _intersection);
  }
  else return false;
}

bool TriangleMesh::intersectBBox(const Ray &_ray)
{
  return true;
}

bool TriangleMesh::intersectMesh(const Ray &_ray, IsectData *_intersection)
{
  bool hasIntersected = false;
  for (Triangle i: m_tris){
    if (i.intersect(_ray, _intersection)){
      hasIntersected = true;
    }
  }
  return hasIntersected;
}

void TriangleMesh::addTri(const Triangle _tri)
{
  m_meshBound.addPoint(_tri.m_v0);
  m_meshBound.addPoint(_tri.m_v1);
  m_meshBound.addPoint(_tri.m_v2);
  m_tris.push_back(_tri);
 // m_meshBound.printData();
}

void TriangleMesh::printData()
{
  for(Triangle i: m_tris) i.printData();
}
