#include <iostream>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Film.hpp"
#include "IsectData.hpp"

Renderer::Renderer(Camera *_cam, Film *_film, std::shared_ptr<TriangleMesh> _mesh):
  m_film(_film),
  m_cam(_cam),
  m_mesh(_mesh)
{
  std::cout << "Renderer created" << std::endl;
}


void Renderer::renderImage()
{
  for (int x = 0; x < m_film->getFilmWidth(); x++){
    for (int y = 0; y < m_film->getFilmHeight(); y++){
      //generate ray
      //std::cout << " rendering pixel " << x << ", " << y << std::endl;
      Ray newRay;
      IsectData intersection;
      m_cam->generateRay(x, y, &newRay);

      //intersect ray with scene
      if (m_mesh->intersect(newRay, &intersection)){
        m_film->setPixle(x, y, intersection.m_n[0]*255,
                               intersection.m_n[1]*255,
                               intersection.m_n[2]*255,
                               255);
      }
      else{
        m_film->setPixle(x, y, 255, 255, 255, 255);
      }
    }
  }
}
