#include <iostream>
#include <thread>

#include "Renderer.hpp"
#include "RenderTask.hpp"
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
  for (int x = 0; x < m_film->getFilmWidth(); x += 32){
    for (int y = 0; y < m_film->getFilmHeight(); y += 32){
      int xInc = 32;
      int yInc = 32;
      if (x + 32 >= m_film->getFilmWidth()){
        xInc = m_film->getFilmWidth() - x - 1;
      }
      if (y + 32 >= m_film->getFilmHeight()){
        yInc = m_film->getFilmHeight() - y - 1;
      }
      std::cout << "creating rendertask" << x << "," << y << "," << x + xInc << "," << y + yInc << "," << std::endl;
      m_tasks.push_back(RenderTask(m_cam,
                                   m_film,
                                   m_scene,
                                   x, y,
                                   x+xInc, y+yInc));
    }
  }
  std::vector<std::thread> threads;
  for (RenderTask &task: m_tasks){
    threads.push_back(std::thread(&RenderTask::render, &task));
    //task.render();
  }
  for (std::thread &task: threads){
    task.join();
  }
}
