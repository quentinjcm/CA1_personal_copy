#include <memory>
#include <algorithm>
#include <math.h>

#include <ngl/Vec3.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/NGLStream.h>

#include "Meshes.hpp"
#include "TriangleMesh.hpp"

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#ifndef M_2PI
#define M_2PI 6.28318530718
#endif


ngl::Vec3 Meshes::circularToCartesian(float _theta, float _phi)
{
  float x = sin(_theta) * cos(_phi);
  float y = sin(_theta) * sin(_phi);
  float z = cos(_theta);

  x = fabs(x)<0.0001? 0: x;
  y = fabs(y)<0.0001? 0: y;
  z = fabs(z)<0.0001? 0: z;

  if (fabs(x) >= 20) std::cout << x << std::endl;
  if (fabs(y) >= 20) std::cout << y << std::endl;
  if (fabs(z) >= 20) std::cout << z << std::endl;

  return ngl::Vec3(x, y, z);
}

std::shared_ptr<TriangleMesh> Meshes::pPlane(float _width, float _height)
{
  auto meshOut = std::make_shared<TriangleMesh>();

  if (_width == 0) _width = 1;
  if (_height == 0) _height = 1;

  _width /= 2;
  _height /= 2;
  ngl::Vec3 v0(-_width, 0, _height);
  ngl::Vec3 v1(_width, 0, _height);
  ngl::Vec3 v2(-_width, 0, -_height);
  ngl::Vec3 v3(_width, 0, -_height);
  ngl::Vec3 n(0, 1, 0);
  ngl::Vec2 uv0(1, 1);
  ngl::Vec2 uv1(0, 1);
  ngl::Vec2 uv2(1, 0);
  ngl::Vec2 uv3(0, 0);

  Triangle t1(v0, v3, v1, n, n, n, uv0, uv3, uv1);
  Triangle t2(v0, v2, v3, n, n, n, uv0, uv2, uv3);

  meshOut->addTri(t1);
  meshOut->addTri(t2);

  return meshOut;
}

std::shared_ptr<TriangleMesh> Meshes::pSphere(float _r, int _sd)
{
  auto meshOut = std::make_shared<TriangleMesh>();

  if (_sd < 4) _sd = 4;
  if (_r == 0) _r = 1;

  float stacks = (float)_sd/2;
  float slices = (float)_sd;

  for (float t = 0; t < stacks; t++){
    float theta1 = (float)t / stacks * M_PI;
    float theta2 = (float)(t + 1) / stacks * M_PI;
    for (float p = 0; p < slices; p++){
      float phi1 = (float)p / slices * M_2PI;
      float phi2 = (float)(p + 1) / slices * M_2PI;

      ngl::Vec3 n0 = circularToCartesian(theta1, phi1);
      ngl::Vec3 n1 = circularToCartesian(theta1, phi2);
      ngl::Vec3 n2 = circularToCartesian(theta2, phi2);
      ngl::Vec3 n3 = circularToCartesian(theta2, phi1);

      ngl::Vec3 v0 = n0 * _r;
      ngl::Vec3 v1 = n1 * _r;
      ngl::Vec3 v2 = n2 * _r;
      ngl::Vec3 v3 = n3 * _r;

      ngl::Vec2 uv0 = ngl::Vec2(t*2/_sd, p/_sd);
      ngl::Vec2 uv1 = ngl::Vec2(t*2/_sd, (p+1)/_sd);
      ngl::Vec2 uv2 = ngl::Vec2((t+1)*2/_sd, (p+1)/_sd);
      ngl::Vec2 uv3 = ngl::Vec2((t+1)*2/_sd, p/_sd);

      if (t == 0){
        Triangle t(v0, v2, v3, n0, n2, n3, uv0, uv2, uv3);
        meshOut->addTri(t);
      }
      else if(t == stacks - 1){
        Triangle t(v2, v0, v1, n2, n0, n1, uv2, uv0, uv1);
        meshOut->addTri(t);
      }
      else{
        Triangle t1(v0, v1, v3, n0, n1, n3, uv0, uv1, uv3);
        Triangle t2(v1, v2, v3, n1, n2, n3, uv1, uv2, uv3);
        meshOut->addTri(t1);
        meshOut->addTri(t2);
      }
    }
  }
  return meshOut;
}
