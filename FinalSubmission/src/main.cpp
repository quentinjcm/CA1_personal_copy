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
#include "BBox.hpp"
#include "Material.hpp"
int main()
{

  Film film(401, 401);

  ngl::Vec3 pos(0, 0, 0);
  ngl::Vec3 lookAt(0, 0, 100);
  ngl::Vec3  up(0, 1, 0);



  Camera cam(pos, lookAt, up, 90.0, &film);

  Ray newRay(ngl::Vec3(0, 0, 0), ngl::Vec3(0, 0, 1));



  //cam.generateRay(200, 200, &newRay);
  std::cout << newRay.m_origin << newRay.m_direction << newRay.m_invDirection << std::endl;


  IsectData intersection;

  //film.show();

  //std::thread task(&Film::show, &film);

  auto mesh = Meshes::scene1();
  auto green = std::make_shared<Material>();
  green->m_diffuseColour = SDL_Color{0, 255, 0, 255};

  std::shared_ptr<Primative> scenePrim = std::make_shared<GeometricPrim>(mesh, green);

  Renderer new_renderer(&cam, &film, scenePrim);

  new_renderer.renderImage();
  //task.join();

  film.show();
  return EXIT_SUCCESS;
}
