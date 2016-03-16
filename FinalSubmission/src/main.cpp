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
#include "SDLWindow.hpp"
#include "AggregatePrim.hpp"
#include "Scene.hpp"

int main()
{

  Film film(401, 401);
  SDLWindow renderWindow(&film);

  ngl::Vec3 pos(100, 0, 20);
  ngl::Vec3 lookAt(0, 0, 100);
  ngl::Vec3  up(1, 1, 0);



  Camera cam(pos, lookAt, up, 90.0, &film);

  Ray newRay(ngl::Vec3(0, 0, 0), ngl::Vec3(0, 0, 1));



  //cam.generateRay(200, 200, &newRay);
  std::cout << newRay.m_origin << newRay.m_direction << newRay.m_invDirection << std::endl;


  IsectData intersection;

  //film.show();

  //std::thread task(&Film::show, &film);
  //init scene
  auto scene = std::make_shared<Scene>();
  auto aggPrim = std::make_shared<AggregatePrim>();

  //bounding cube
  auto boxMesh = Meshes::sceneBox();
  auto boxMat = std::make_shared<Material>();
  boxMat->m_diffuseColour = SDL_Color{0, 255, 0, 255};
  auto boxPrim = std::make_shared<GeometricPrim>(boxMesh, boxMat);// or <prim>?
  aggPrim->addPrimative(boxPrim);

  //torus
  auto torusMesh = Meshes::Torus();
  auto torusMat = std::make_shared<Material>();
  torusMat->m_diffuseColour = SDL_Color{0, 255, 255, 255};
  auto torusPrim = std::make_shared<GeometricPrim>(torusMesh, torusMat);// or <prim>?
  aggPrim->addPrimative(torusPrim);

  //block
  auto blockMesh = Meshes::Block();
  auto blockMat = std::make_shared<Material>();
  blockMat->m_diffuseColour = SDL_Color{100, 50, 0, 255};
  auto blockPrim = std::make_shared<GeometricPrim>(blockMesh, blockMat);// or <prim>?
  aggPrim->addPrimative(blockPrim);

  //sphere
  auto sphereMesh = Meshes::Sphere();
  auto sphereMat = std::make_shared<Material>();
  sphereMat->m_diffuseColour = SDL_Color{100, 100, 100, 255};
  auto spherePrim = std::make_shared<GeometricPrim>(sphereMesh, sphereMat);// or <prim>?
  aggPrim->addPrimative(spherePrim);


  scene->setSceneGeo(aggPrim);
  Renderer new_renderer(&cam, &film, scene);

  new_renderer.renderImage();
  //task.join();

  //film.show();
  renderWindow.run();
  return EXIT_SUCCESS;
}
