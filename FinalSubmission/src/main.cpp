#include <iostream>
#include <memory>
#include <vector>
#include <thread>

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/NGLStream.h>


#include "TriangleMesh.hpp"
#include "Triangle.hpp"
#include "IsectData.hpp"
#include "Film.hpp"
#include "Camera.hpp"
#include "GeometricPrim.hpp"
#include "Meshes.hpp"
#include "Renderer.hpp"
//#include "BBox.hpp"
int main()
{

  Film film(401, 401);

  ngl::Vec3 pos(0, 0, 20);
  ngl::Vec3 lookAt(0.5, 0.5, 0.5);
  ngl::Vec3  up(0, 1, 0);



  Camera cam(pos, lookAt, up, 90.0, &film);

  Ray newRay;
  cam.generateRay(200, 200, &newRay);
  std::cout << newRay.m_origin << newRay.m_direction << std::endl;

  ngl::Vec3 bbMin(0, 0, 0);
  ngl::Vec3 bbMax(1, 1, 1);

  BBox smallBox(bbMin, bbMax);

  smallBox.printData();

  if (smallBox.intersect(newRay)){
      std::cout << "hit bbox!" << std::endl;
  }

  //making triangle
  //ngl::Vec3 v1(0, 0, 0);
  //ngl::Vec3 v2(1, 0, 0);
  //ngl::Vec3 v3(0, 1, 0);
  //Triangle t1(v1, v2, v3);
  //std::shared_ptr<TriangleMesh> m1 = std::make_shared<TriangleMesh>();
  //m1->addTri(t1);
  //m1->printData();

  IsectData intersection;


  //m1->intersect(newRay, &intersection);

  //film.show();

  //std::thread task(&Film::show, &film);

  //auto mesh = Meshes::scene1();

  //Renderer new_renderer(&cam, &film, mesh);

  //new_renderer.renderImage();
  //task.join();

  //film.show();

  return EXIT_SUCCESS;
}
