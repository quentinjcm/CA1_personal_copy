#include <iostream>
#include <thread>

#include "Renderer.hpp"
#include "RenderTask.hpp"
#include "Camera.hpp"
#include "Film.hpp"
#include "IsectData.hpp"
#include "Primative.hpp"

Renderer::Renderer(Camera *_cam, Film *_film, std::shared_ptr<Scene> _scene, int _aa):
  m_film(_film),
  m_cam(_cam),
  m_scene(_scene),
  m_aa(_aa)
{
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
      m_tasks.push_back(RenderTask(m_cam,
                                   m_film,
                                   m_scene,
                                   x, y,
                                   x+xInc, y+yInc,
                                   m_aa));
    }
  }
  std::vector<std::thread> threads;
  bool multiThread = true;
  std::cout << "starting render" << std::endl;
  if (multiThread){
    for (RenderTask &task: m_tasks){
      threads.push_back(std::thread(&RenderTask::render, &task));
    }
    for (std::thread &task: threads){
      task.join();
    }
  }
  else{
    for (RenderTask &task: m_tasks){
      task.render();
    }
  }
}
