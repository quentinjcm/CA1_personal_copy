#include <iostream>
#include <memory>
#include <vector>
#include <thread>

#include <QTime>
#include <qimage.h>
#include <QImageReader>

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
#include "SceneParser.hpp"

int main()
{


  Film film(1280, 720);
  SDLWindow renderWindow(&film);

  ngl::Vec3 pos(10, 50, -30);
  ngl::Vec3 lookAt(0, 0, 0);
  ngl::Vec3  up(0, 1, 0);

  Camera cam(pos, lookAt, up, 100.0, &film);

  //init scene
  std::shared_ptr<Scene> scene = std::make_shared<Scene>();
  SceneParser p("scenes/scene1.txt", scene);
  p.parseScene();

  QTime startTime;
  startTime.start();

  Renderer new_renderer(&cam, &film, scene, 0);

  new_renderer.renderImage();

  std::cout << std::endl << "rendered in: " << startTime.elapsed()/1000.0 << " seconds" << std::endl;

  renderWindow.run();

  /*
  QList<QByteArray> formats = QImageReader::supportedImageFormats();
    for ( QList<QByteArray>::Iterator f = formats.begin(); f != formats.end(); ++ f )
      printf("%s , ", f->constData() );
  */

  return EXIT_SUCCESS;
}
