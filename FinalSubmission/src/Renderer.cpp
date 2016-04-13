#include <iostream>
#include <thread>

#include "Renderer.hpp"
#include "RenderTask.hpp"
#include "Camera.hpp"
#include "Film.hpp"
#include "IsectData.hpp"
#include "Primative.hpp"

/// @file Renderer.cpp
/// @brief implementation file for the Renderer class

 Renderer::Renderer(std::shared_ptr<Scene> _scene, std::shared_ptr<RenderSettings> _settings, Film *_film):
   m_film(_film),
   m_scene(_scene),
   m_settings(_settings)
 {
   //construct camera
   m_cam = Camera(m_settings->m_camPos,
                                  m_settings->m_camTarget,
                                  m_settings->m_camUp,
                                  m_settings->m_fov,
                                  m_settings->m_filmWidth,
                                  m_settings->m_filmHeight);
 }


void Renderer::renderImage()
{
  //setting up the render tasks
  std::cout << "Creating render tasks" << std::endl;
  int xInc = m_settings->m_threadWidth;
  int yInc = m_settings->m_threadHeight;
  for (int x = 0; x < m_settings->m_filmWidth; x += xInc)
  {
    for (int y = 0; y < m_settings->m_filmHeight; y += yInc)
    {
      // checking to see if the task goes beyound the edge of the image
      // temp values created so that they can be changed without affecting
      // xInc and yInc.
      int xIncTemp = xInc;
      int yIncTemp = yInc;
      //if x has gone over
      if (x + xIncTemp > m_settings->m_filmWidth)
      {
        // set the temp increment to the value that will take it to the edge of the image
        xIncTemp = m_settings->m_filmWidth - x;
      }
      // if y has gone over
      if (y + yIncTemp > m_settings->m_filmHeight)
      {
        // set the temp increment to the value that will take it to the edge of the image
        yIncTemp = m_settings->m_filmHeight - y;
      }
      // constructing the task
      m_tasks.push_back(RenderTask(&m_cam,
                                   m_film,
                                   m_scene,
                                   x, y,
                                   x+xIncTemp, y+yIncTemp,
                                   m_settings));
    }
  }
  std::cout << m_tasks.size() <<" tasks created" << std::endl;

  // setting up multithreading with std::thread
  std::vector<std::thread> threads;
  std::cout << "starting render" << std::endl;
  if (m_settings->m_multithread)
  {
    for (RenderTask &task: m_tasks)
    {
      // because I need to join each of the tasks onece finished, i create them in a vector
      threads.push_back(std::thread(&RenderTask::render, &task));
    }
    for (std::thread &task: threads)
    {
      // run through the taks and wait for each one to finish
      // this ensures that all tasks are finished before the program continues
      task.join();
    }
  }
  else{
    // if there is no multithreading set by the user, the tasks will rendere one by one
    for (RenderTask &task: m_tasks)
    {
      task.render();
    }
  }
}
