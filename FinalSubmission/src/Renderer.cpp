#include <iostream>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Film.hpp"
#include "IsectData.hpp"
#include "Primative.hpp"

Renderer::Renderer(Camera *_cam, Film *_film, std::shared_ptr<Primative> _scene):
  m_film(_film),
  m_cam(_cam),
  m_scene(_scene)
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
      if (m_scene->intersect(newRay, &intersection)){
        m_film->setNormalPixle(x, y, intersection.m_n);
        m_film->setDepthPixel(x, y, intersection.m_t);
        m_film->setDiffusePixel(x, y, intersection.m_material->m_diffuseColour);
      }
      else{
        m_film->setNormalPixle(x, y, ngl::Vec3(0, 0, 0));
        m_film->setDepthPixel(x, y, 0);
        m_film->setDiffusePixel(x, y, SDL_Color{0, 0, 0, 1});
      }
    }
  }
}
