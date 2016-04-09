#include <iostream>
#include <thread>

#include "Renderer.hpp"
#include "RenderTask.hpp"
#include "Camera.hpp"
#include "Film.hpp"
#include "IsectData.hpp"
#include "Primative.hpp"

 Renderer::Renderer(std::shared_ptr<Scene> _scene, std::shared_ptr<RenderSettings> _settings, Film *_film):
   m_scene(_scene),
   m_film(_film),
   m_settings(_settings)
 {
   //construct camera
   m_cam = Camera(m_settings->m_camPos,
                                  m_settings->m_camAim,
                                  m_settings->m_camUp,
                                  m_settings->m_fov,
                                  m_settings->m_filmWidth,
                                  m_settings->m_filmHeight);
 }


void Renderer::renderImage()
{
  //replace film with rendersettings
  int xInc = m_settings->m_threadWidth;
  int yInc = m_settings->m_threadHeight;
  for (int x = 0; x < m_settings->m_filmWidth; x += xInc){
    for (int y = 0; y < m_settings->m_filmHeight; y += yInc){
      int xIncTemp = xInc;
      int yIncTemp = yInc;
      if (x + xIncTemp > m_settings->m_filmWidth){
        xIncTemp = m_settings->m_filmWidth - x ;
      }
      if (y + yIncTemp > m_settings->m_filmHeight){
        yIncTemp = m_settings->m_filmHeight - y ;
      }
      m_tasks.push_back(RenderTask(&m_cam,
                                   m_film,
                                   m_scene,
                                   x, y,
                                   x+xIncTemp, y+yIncTemp,
                                   m_settings));
    }
  }
  std::vector<std::thread> threads;
  bool multiThread = m_settings->m_multithread;
  std::cout << "starting render" << std::endl;
  if (multiThread){
    for (RenderTask &task: m_tasks){
      //std::cout << "num threads: " << threads.size() << std::endl;

      threads.push_back(std::thread(&RenderTask::render, &task));
    }
   // std::cout << "final threads:: " << threads.size() << std::endl;
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
