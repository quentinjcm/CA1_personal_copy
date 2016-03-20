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

int main()
{
  QTime startTime;
  startTime.start();

  Film film(1280, 720);
  SDLWindow renderWindow(&film);

  ngl::Vec3 pos(-20, 30, -40);
  ngl::Vec3 lookAt(0, -10, 0);
  ngl::Vec3  up(0, 1, 0);



  Camera cam(pos, lookAt, up, 100.0, &film);

  Ray newRay(ngl::Vec3(0, 0, 0), ngl::Vec3(0, 0, 1));


  //cam.generateRay(200, 200, &newRay);
  std::cout << newRay.m_origin << newRay.m_direction << newRay.m_invDirection << std::endl;


  IsectData intersection;

  //film.show();

  //std::thread task(&Film::show, &film);
  //init scene
  auto scene = std::make_shared<Scene>();
  //auto aggPrim = std::make_shared<AggregatePrim>();

//*
  //groundPlane
  auto planeMesh = Meshes::Plane();
  auto planeMat = std::make_shared<Material>("textures/grid1k.jpg");
  planeMat->m_diffuseColour = SDL_Color{0, 100, 100, 255};
  auto planePrim = std::make_shared<GeometricPrim>(planeMesh, planeMat);// or <prim>?
  //scene->addPrim(planePrim);
// */
  //*
    //sphere
    auto sphereMesh = Meshes::SphereUV();
    auto spherePrim = std::make_shared<GeometricPrim>(sphereMesh, planeMat);// or <prim>?
    scene->addPrim(spherePrim);
  // */
 /*
  //bounding cube
  auto boxMesh = Meshes::sceneBox();
  auto boxMat = std::make_shared<Material>();
  boxMat->m_diffuseColour = SDL_Color{0, 255, 0, 255};
  auto boxPrim = std::make_shared<GeometricPrim>(boxMesh, boxMat);// or <prim>?
  scene->addPrim(boxPrim);
 */
 /*
  //torus
  auto torusMesh = Meshes::Torus();
  auto torusMat = std::make_shared<Material>();
  torusMat->m_diffuseColour = SDL_Color{0, 255, 255, 255};
  auto torusPrim = std::make_shared<GeometricPrim>(torusMesh, torusMat);// or <prim>?
  scene->addPrim(torusPrim);
 */
/*
  //block
  auto blockMesh = Meshes::Block();
  auto blockMat = std::make_shared<Material>();
  blockMat->m_diffuseColour = SDL_Color{100, 50, 0, 255};
  auto blockPrim = std::make_shared<GeometricPrim>(blockMesh, blockMat);// or <prim>?
  scene->addPrim(blockPrim);
*/
/*
  //sphere
  auto sphereMesh = Meshes::Sphere();
  auto sphereMat = std::make_shared<Material>();
  sphereMat->m_diffuseColour = SDL_Color{100, 100, 100, 255};
  auto spherePrim = std::make_shared<GeometricPrim>(sphereMesh, sphereMat);// or <prim>?
  scene->addPrim(spherePrim);
*/

  //scene->setSceneGeo(aggPrim);
  Renderer new_renderer(&cam, &film, scene);

  new_renderer.renderImage();

  std::cout << std::endl << "rendered in: " << startTime.elapsed()/1000.0 << " seconds" << std::endl;


  //task.join();

    //film.show();
  renderWindow.run();
  //TextureFile board("textures/checkerboard.jpg");
  //board.loadImage();

  return EXIT_SUCCESS;
}
