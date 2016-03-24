#include <iostream>
#include <memory>
#include <vector>
#include <thread>

#include <QTime>

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
#include "SDLWindow.hpp"
#include "Scene.hpp"
#include "TextureFile.hpp"
#include "Light.hpp"

int main()
{


  Film film(1280, 720);
  SDLWindow renderWindow(&film);

  ngl::Vec3 pos(10, 50, 30);
  ngl::Vec3 lookAt(0, 0, 0);
  ngl::Vec3  up(0, 1, 0);

  Camera cam(pos, lookAt, up, 100.0, &film);

  IsectData intersection;

  //init scene
  std::shared_ptr<Scene> scene = std::make_shared<Scene>();

  //a single light
  Light l1(ngl::Vec3(20, 50, 0),
           ngl::Colour(1.f, 0.7f, 0.7f, 1.0f),
           4);
  scene->addLight(l1);

  Light l2(ngl::Vec3(-20, 50, 0),
           ngl::Colour(0.7f, 1.0f, 0.7f, 1.0f),
           4);
  scene->addLight(l2);


  //groundPlane
  auto planeMesh = Meshes::Plane();
  auto planeMat = std::make_shared<Material>("textures/grid1k.jpg"); //
  planeMat->m_diffuseColour = ngl::Colour(0, 0.5, 0.5, 1.0);
  planeMat->m_smoothness = 20;
  planeMat->m_f0 = 1;

  auto planePrim = std::make_shared<GeometricPrim>(planeMesh, planeMat);// or <prim>?
  scene->addPrim(planePrim);

  //sphere
  auto sphereMesh = Meshes::Sphere3();
  auto spherePrim = std::make_shared<GeometricPrim>(sphereMesh, planeMat);// or <prim>?
  scene->addPrim(spherePrim);

  //scene->setSceneGeo(aggPrim);
  QTime startTime;
  startTime.start();

  Renderer new_renderer(&cam, &film, scene, 0);

  new_renderer.renderImage();

  std::cout << std::endl << "rendered in: " << startTime.elapsed()/1000.0 << " seconds" << std::endl;

  renderWindow.run();

  return EXIT_SUCCESS;
}
