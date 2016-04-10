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
  bool hasIntersected = false;
  if (m_meshBound.intersect(_ray)){
    for (Triangle i: m_tris){
      if (i.intersect(_ray, _intersection)){
        hasIntersected = true;
      }
    }
  }
  return hasIntersected;
}

bool TriangleMesh::sIntersect(const Ray &_ray)
{
  if (m_meshBound.intersect(_ray)){
    IsectData dummy;
    for (Triangle i: m_tris){
      if (i.intersect(_ray, &dummy)){
        return true;
      }
    }
  }
  return false;
}

void TriangleMesh::addTri(const Triangle _tri)
{
  m_meshBound.addPoint(_tri.m_v0);
  m_meshBound.addPoint(_tri.m_v1);
  m_meshBound.addPoint(_tri.m_v2);
  m_tris.push_back(_tri);
}

void TriangleMesh::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  for (Triangle t: m_tris){
    t.getGLData(_points, _normals);
  }
}

