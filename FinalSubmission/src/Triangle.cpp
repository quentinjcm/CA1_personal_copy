#include <iostream>
#include <cmath>

#include <ngl/Vec3.h>
#include <ngl/NGLStream.h>
#include <ngl/Vec2.h>

#include "Triangle.hpp"
#include "TriangleData.hpp"
#include "Ray.hpp"

///@file Triangle.cpp
///@brief Implementation file for the Triangle class

Triangle::Triangle(ngl::Vec3 _v0, ngl::Vec3 _v1, ngl::Vec3 _v2,
                   ngl::Vec3 _n0, ngl::Vec3 _n1, ngl::Vec3 _n2,
                   ngl::Vec2 _uv0,ngl::Vec2 _uv1,ngl::Vec2 _uv2):
  m_v0(_v0), m_v1(_v1), m_v2(_v2)
{
  m_data = std::make_shared<TriangleData>(_n0, _n1, _n2, _uv0, _uv1, _uv2);
  calcN();
  calcD();
  calcDominantAxis();
}

bool Triangle::intersect(const Ray &_ray, IsectData *_intersection)
{
  /**
   * The intersection algorithm used here can be found at
   * http://graphics.stanford.edu/courses/cs348b-98/gg/intersect.html
   * accessed on 08/03/2016
   * Firstly the intersection of the plane made form the 3 verticies
   * and the ray is found. Then this point is checked to see if is is
   * inside the triangle. This is done by projecting the triangle along
   * the major axis of the normal, reducing the problem to 2 dimensions.
   * Then the vector m_v0->p is written prametrically in terms of the
   * vectors alpha(m_v0->m_v1) and beta(m_v0->m_v2). If alpha > 0 and
   * beta > 0 and (alpha + beta < 1) then the point of intersection is
   * inside the triangle.
   */
  //first the ray is checked to se if it is parrallel to the plane
  double denominator = m_n.dot(_ray.m_direction);
  //if not parrallel, then check for intersection with plane
  if (denominator){
    double numerator = m_d + m_n.dot(_ray.m_origin);
    //t strores the parameter for the distance along the ray of the intersection: r(t) = O + Dt
    double t = -numerator/denominator;
    //if intersection point is behind the rays origin, the ray is rejected

    if (t <= 0){
      //std::cout << "T less than 0" << std::endl;
      return false;
    }
    //if a cloaser intersection has already been found, the ray is rejected
    if (t > _intersection->m_t | t > _ray.m_maxT){
      //std::cout << "intersection further away than closest intersection" << std::endl;
      return false;
    }
    //now the intersection point is calculated
    ngl::Vec3 p = _ray.m_origin + _ray.m_direction * t;
    //checking to see if the point is inside the triangle by
    //projecting the triangle along the major axis of the normal
    //[u0, v0] = vector from m_v0 to intersection point
    double u0 = p[m_i1] - m_v0[m_i1];
    double v0 = p[m_i2] - m_v0[m_i2];
    //[u1, v1] = vector from m_v0 to m_v1
    double u1 = m_v1[m_i1] - m_v0[m_i1];
    double v1 = m_v1[m_i2] - m_v0[m_i2];
    //[u2, v2] = vector from m_v0 to m_v2
    double u2 = m_v2[m_i1] - m_v0[m_i1];
    double v2 = m_v2[m_i2] - m_v0[m_i2];

    //setting alpha and beta to be balues that indicate no intersection
    double alpha = -1;
    double beta = -1;

    //setting the values of alpha and beta
    if (u1 == 0){
      beta = u0/u2;
      if (beta >= 0 & beta <= 1){
        alpha = (v0 - beta * v2)/v1;
      }
    }
    else{
      beta = (v0*u1 - u0*v1) / (v2*u1 - u2*v1);
      if (beta >= 0 and beta <= 1){
        alpha = (u0 - beta*u2) / u1;
      }
    }
    if (alpha >= 0 & beta >= 0 & (alpha + beta) <=1){
      //filling the intersction data structure with data about the intersection point
      ngl::Vec3 interpolatedNormal = m_data->m_n0 * (1 - (alpha + beta)) + m_data->m_n1 * alpha + m_data->m_n2 * beta;
      ngl::Vec2 interpolatedUV(m_data->m_uv0[0] * (1 - (alpha + beta)) + m_data->m_uv1[0] * alpha + m_data->m_uv2[0] * beta,
                               m_data->m_uv0[1] * (1 - (alpha + beta)) + m_data->m_uv1[1] * alpha + m_data->m_uv2[1] * beta);
      _intersection->m_t = t;
      _intersection->m_pos = p;
      _intersection->m_n = interpolatedNormal;
      _intersection->m_uv = interpolatedUV;
      _intersection->m_eyeDir = _ray.m_direction;
      _intersection->m_eyeDir.normalize();
      return true;
    }
    else{
      //intersection outside triangl
      return false;
    }
  }
  else{
    //ray is parrallel to triangle
    return false;
  }
}

void Triangle::printData()
{
  std::cout << "Printing triangle data:\n";
  std::cout << "points:\n";
  std::cout << m_v0 << "\n" << m_v1 << "\n" << m_v2 << std::endl;

  std::cout << "normals:\n";
  std::cout << m_data->m_n0 << "\n" << m_data->m_n1 << "\n" << m_data->m_n2 << std::endl;

  std::cout << "n: " << m_n << std::endl;

  std::cout << "d: " << m_d << std::endl;
 }

void Triangle::calcN()
{
  m_n = ngl::calcNormal(m_v0, m_v1, m_v2);
  m_n.normalize();
}

void Triangle::calcD()
{
  m_d = (m_n.dot(m_v0)) * -1;
}

void Triangle::calcDominantAxis()
{
  double x = fabs(m_n.m_x);
  double y = fabs(m_n.m_y);
  double z = fabs(m_n.m_z);
  if (x > y & x > z){
    //x is the dominant axis
    m_i1 = 1;
    m_i2 = 2;
  }
  else if (y > x & y > z){
    //y is the dominant axis
    m_i1 = 2;
    m_i2 = 0;
  }
  else{
    //z is the dominant axis
    m_i1 = 0;
    m_i2 = 1;
  }
}

void Triangle::getGLData(std::vector<ngl::Vec3> *_points, std::vector<ngl::Vec3> *_normals)
{
  std::cout << "getting triangle data" << std::endl;
  _points->push_back(m_v0);
  _points->push_back(m_v1);
  _points->push_back(m_v2);
  _normals->push_back(m_data->m_n0);
  _normals->push_back(m_data->m_n1);
  _normals->push_back(m_data->m_n2);
}
