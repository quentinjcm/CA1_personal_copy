#include <memory>
#include <algorithm>
#include <math.h>

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Mat3.h>
#include <ngl/Transformation.h>
#include <ngl/NGLStream.h>

#include "ProceduralMeshes.hpp"

//defines for pi and 2*pi
#ifndef M_PI
#define M_PI 3.14159265359
#endif

#ifndef M_2PI
#define M_2PI 6.28318530718
#endif

/// @file ProceduralMeshes.cpp
/// @brief implementation file for the ProceduralMeshes class

ngl::Vec3 ProceduralMeshes::circularToCartesian(double _theta, double _phi)
{
  double x = sin(_theta) * cos(_phi);
  double y = sin(_theta) * sin(_phi);
  double z = cos(_theta);

  //limiting the size of x y and z because I was getting problems with values
  //that were very close to 0 and numerical accuracy wasnt a huge consern.
  x = fabs(x)<0.0001? 0: x;
  y = fabs(y)<0.0001? 0: y;
  z = fabs(z)<0.0001? 0: z;

  return ngl::Vec3(x, y, z);
}

std::shared_ptr<TriangleMesh> ProceduralMeshes::pPlane(double _width, double _height, ngl::Transformation &_t)
{
  auto meshOut = std::make_shared<TriangleMesh>();


  ngl::Mat4 t(_t.getMatrix());
  ngl::Mat3 nt(t);
  nt.transpose();
  nt.inverse();
  //std::cout << t << std::endl;
  //setting a minimum size for the plane
  if (_width == 0) _width = 1;
  if (_height == 0) _height = 1;

  //dividing the width and height by 2 to sencer the plane on the origin
  _width /= 2;
  _height /= 2;

  /* vertex layout for the plane
   *  0-----1
   *  | \   |
   *  |   \ |
   *  2-----3
   */
  //going through all 4 points of the plane and setting the positions, uvs and normal
  ngl::Vec3 v0(-_width, 0, _height);
  ngl::Vec3 v1(_width, 0, _height);
  ngl::Vec3 v2(-_width, 0, -_height);
  ngl::Vec3 v3(_width, 0, -_height);
  //because the plane faces up, it only needs one normal for all 4 points
  ngl::Vec3 n(0, 1, 0);
  ngl::Vec2 uv0(0, 0);
  ngl::Vec2 uv1(1, 0);
  ngl::Vec2 uv2(0, 1);
  ngl::Vec2 uv3(1, 1);

  //transofrming points
  v0 = ngl::Vec4(v0) * t;
  v1 = ngl::Vec4(v1) * t;
  v2 = ngl::Vec4(v2) * t;
  v3 = ngl::Vec4(v3) * t;

  n = n * nt;
  //std::cout << v0 << std::endl;

  Triangle t1(v0, v1, v3, n, n, n, uv0, uv1, uv3);
  Triangle t2(v0, v3, v2, n, n, n, uv0, uv3, uv2);

  meshOut->addTri(t1);
  meshOut->addTri(t2);

  return meshOut;
}

std::shared_ptr<TriangleMesh> ProceduralMeshes::pSphere(double _r, int _sd, ngl::Transformation &_t)
{

  auto meshOut = std::make_shared<TriangleMesh>();

  ngl::Mat4 transform(_t.getMatrix());
  ngl::Mat3 nTransform(transform);
  nTransform.inverse();

  //limiting the minimum number of subdivisions to 4 and radius to 1 of it is set to 0
  if (_sd < 4) _sd = 4;
  if (_r == 0) _r = 1;

  //I chose to have only a single parameter to specify subdivisions
  //there are an equal number of divisions in the xz plane and xy plane
  double stacks = (double)_sd/2;
  double slices = (double)_sd;

  for (double t = 0; t < stacks; t++)
  {
    //converting current and next stack value to sperical coordinates
    double theta1 = (double)t / stacks * M_PI;
    double theta2 = (double)(t + 1) / stacks * M_PI;
    for (double p = 0; p < slices; p++)
    {
      //converting current and next slice value to sperical coordinates
      double phi1 = (double)p / slices * M_2PI;
      double phi2 = (double)(p + 1) / slices * M_2PI;

      //at radius 1 the algorithm generates a unit sphere where each vertex
      //is its own normal, I can therfor generate the normals and multiply
      //them by the radius to get the vertex positions
      //converting the 4 sperical coordinates to cartesian for the normals
      ngl::Vec3 n0 = circularToCartesian(theta1, phi1);
      ngl::Vec3 n1 = circularToCartesian(theta1, phi2);
      ngl::Vec3 n2 = circularToCartesian(theta2, phi2);
      ngl::Vec3 n3 = circularToCartesian(theta2, phi1);
      ngl::Vec3 v0 = n0 * _r;
      ngl::Vec3 v1 = n1 * _r;
      ngl::Vec3 v2 = n2 * _r;
      ngl::Vec3 v3 = n3 * _r;

      //uv cordinates use the stack and slice values. This is an easy way
      // to uv a sphere but it does create pinching around the poles
      ngl::Vec2 uv0 = ngl::Vec2(t*2/_sd, p/_sd);
      ngl::Vec2 uv1 = ngl::Vec2(t*2/_sd, (p+1)/_sd);
      ngl::Vec2 uv2 = ngl::Vec2((t+1)*2/_sd, (p+1)/_sd);
      ngl::Vec2 uv3 = ngl::Vec2((t+1)*2/_sd, p/_sd);

      //transforming points and normals
      v0 = ngl::Vec4(v0) * transform;
      v1 = ngl::Vec4(v1) * transform;
      v2 = ngl::Vec4(v2) * transform;
      v3 = ngl::Vec4(v3) * transform;

      n0 = n0 * nTransform;
      n1 = n1 * nTransform;
      n2 = n2 * nTransform;
      n3 = n3 * nTransform;
      //triangle is at the base and only one triangle should be created
      if (t == 0)
      {
        Triangle t(v0, v2, v3, n0, n2, n3, uv0, uv2, uv3);
        meshOut->addTri(t);
      }
      //triangle is at the tip and only one should be created
      else if(t == stacks - 1)
      {
        Triangle t(v2, v0, v1, n2, n0, n1, uv2, uv0, uv1);
        meshOut->addTri(t);
      }
      //triangle is neither at the tip or base and we therfor need 2 to fill the quad
      else
      {
        Triangle t1(v0, v1, v3, n0, n1, n3, uv0, uv1, uv3);
        Triangle t2(v1, v2, v3, n1, n2, n3, uv1, uv2, uv3);
        meshOut->addTri(t1);
        meshOut->addTri(t2);
      }
    }
  }
  //returning the now full mesh
  return meshOut;
}
