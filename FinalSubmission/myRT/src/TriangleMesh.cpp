#include <iostream>
#include <vector>
#include "ngl/Vec3.h"
#include "TriangleMesh.hpp"
#include "Triangle.hpp"
#include "Ray.hpp"
#include "BBox.hpp"

///@file TriangleMesh.cpp
///@brief Implementation file for the TriangleMesh class

bool TriangleMesh::intersect(const Ray &_ray, IsectData *_intersection)
{
  // calls the intersect method for all of the triangles in the mesh
  // _intersection will be filled up with data for the closest one
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
  // calls the intersect method for triangles untill it finds an intersection
  // so it stops as soon as it knows its in shaddow
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
  // adds each vertex to the bbox
  m_meshBound.addPoint(_tri.getV0());
  m_meshBound.addPoint(_tri.getV1());
  m_meshBound.addPoint(_tri.getV2());

  // then pushes the tri onto the vector
  m_tris.push_back(_tri);
}

void TriangleMesh::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  for (Triangle t: m_tris){
    t.getGLData(_points, _normals);
  }
}

