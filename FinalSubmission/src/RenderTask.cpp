#include <memory>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <ngl/NGLStream.h>
#include <ngl/Colour.h>

#include <SDL2/SDL.h>

#include "RenderTask.hpp"
#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"
#include "Material.hpp"



RenderTask::RenderTask(Camera *_cam,
                       Film *_film,
                       std::shared_ptr<Scene> _scene,
                       int _xMin, int _yMin,
                       int _xMax, int _yMax,
                       int _aa):
  m_cam(_cam),
  m_film(_film),
  m_scene(_scene),
  m_xMin(_xMin),
  m_yMin(_yMin),
  m_xMax(_xMax),
  m_yMax(_yMax),
  m_aa(_aa)
{
}

void RenderTask::render()
{
  m_distribution = std::uniform_real_distribution<float>(-0.5, 0.5);
  for (int x = m_xMin; x < m_xMax; x++){
    for (int y = m_yMin; y < m_yMax; y++){
      //std::cout << m_aa << std::endl;
      if (m_aa){
        renderPixelAA((float)x, (float)y);
      }
      else{
        renderPixel((float)x, (float)y);
      }
    }
  }
}



void RenderTask::renderPixel(float _x, float _y)
{
  Ray newRay;
  IsectData intersection;
  intersection.m_depth = 1;
  m_cam->generateRay(_x, _y, &newRay);
  if (m_scene->intersect(newRay, &intersection)){
    m_film->setDepthPixel(_x, _y, depthPixel(intersection.m_t));
    m_film->setNormalPixle(_x, _y, normalPixel(intersection.m_n));
    m_film->setDiffusePixel(_x, _y, colourPixel(&intersection));
  }
  else{
    m_film->setDepthPixel(_x, _y, ngl::Colour(0, 0, 0, 1.0));
    m_film->setNormalPixle(_x, _y, ngl::Colour(0, 0, 0, 1.0));
    m_film->setDiffusePixel(_x, _y, ngl::Colour(0, 0, 0, 1.0));
  }
}

void RenderTask::renderPixelAA(float _x, float _y){
  ngl::Colour depthPixelSum(0, 0, 0, 1);
  ngl::Colour colourPixelSum(0, 0, 0, 1);
  ngl::Colour normalPixelSum(0, 0, 0, 1);
  for (int i = 0; i < m_aa; i++){
    Ray newRay;
    IsectData intersection;
    intersection.m_depth = 1;
    m_cam->generateRay(_x + m_distribution(m_generator),
                       _y + m_distribution(m_generator),
                       &newRay);
    if (m_scene->intersect(newRay, &intersection)){
      depthPixelSum += depthPixel(intersection.m_t);
      normalPixelSum += normalPixel(intersection.m_n);
      colourPixelSum += colourPixel(&intersection);
    }
  }
  depthPixelSum *= 1.0/(float)m_aa;
  colourPixelSum *= 1.0/(float)m_aa;
  normalPixelSum *= 1.0/(float)m_aa;
  m_film->setDepthPixel(_x, _y, depthPixelSum);
  m_film->setNormalPixle(_x, _y, normalPixelSum);
  m_film->setDiffusePixel(_x, _y, colourPixelSum);
}

ngl::Colour RenderTask::normalPixel(ngl::Vec3 _normal)
{
  ngl::Colour normal(_normal[0],
                     _normal[1],
                     _normal[2],
                     1.0);
  normal.clamp(0, 1);
  return normal;
}

ngl::Colour RenderTask::depthPixel(float _depth)
{
  ngl::Colour depth(_depth/255.0,
                    _depth/255.0,
                    _depth/255.0,
                    1.0);
  depth.clamp(0, 1);
  return depth;
}

ngl::Colour RenderTask::colourPixel(IsectData *_intersection)
{
  ngl::Colour outColour(0, 0, 0, 1);
  ngl::Colour matColour = _intersection->m_material->getDiffuseColour(_intersection->m_uv[0],
                                                                      _intersection->m_uv[1]);

  //ambient lighting
  ngl::Colour ambientLighting(0.2, 0.2, 0.2, 1);
  outColour += ambientLighting * matColour; //ambient

  for (Light &l: m_scene->m_sceneLights){
    if(isVisible(_intersection->m_pos, l.m_pos)){
      ngl::Vec3 normal(_intersection->m_n);
      ngl::Vec3 lightDir(l.m_pos - _intersection->m_pos);
      ngl::Vec3 eyeDir(_intersection->m_eyeDir * -1);
      ngl::Vec3 reflectDir(normal * 2 * (normal.dot(eyeDir)) - eyeDir);
      ngl::Vec3 halfVec(lightDir + eyeDir);

      lightDir.normalize();
      eyeDir.normalize();
      reflectDir.normalize();
      halfVec.normalize();

      float NdotH = std::max(0.0f, (float)normal.dot(halfVec));
      float NdotL = std::max(0.0f, (float)normal.dot(lightDir));
      float reflectionIntensity = fSchlick(_intersection->m_material->m_f0, eyeDir, normal);


      ngl::Colour reflectionCol(.2, .2, .2, 1);


      //outColour += reflectionCol * reflectionIntensity;
      outColour += l.m_colour * std::pow(NdotH, _intersection->m_material->m_smoothness); //specular
      outColour += l.m_colour * NdotL * matColour; //diffuse
    }
  }
  outColour.clamp(0, 1);
  return outColour;
}

bool RenderTask::isVisible(ngl::Vec3 _point, ngl::Vec3 _lightPos)
{
  ngl::Vec3 direction = _lightPos - _point;
  _point += direction*0.001;
  Ray shadowRay(_point, direction);
  IsectData dummy;
  if (m_scene->intersect(shadowRay, &dummy)){
    return false;
  }
  return true;


}

float RenderTask::fSchlick(float f0, ngl::Vec3 _l, ngl::Vec3 _n)
{
  return f0 + (1 - f0) * pow(1 - (_l.dot(_n)), 5);
}

ngl::Colour RenderTask::reflectedLighting(IsectData *_intersection)
{
  return ngl::Colour(0, 0, 0, 1);
}







