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
  std::vector<ngl::Vec2> samples;
  samples.push_back(ngl::Vec2(_x, _y));
  m_film->setDiffusePixel(_x, _y, renderPixel(samples));
  /*
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
  */
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
  ngl::Colour depth(1-(_depth/255.0),
                    1-(_depth/255.0),
                    1-(_depth/255.0),
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
      ngl::Vec3 eyeDir(_intersection->m_eyeDir);
      ngl::Vec3 reflectDir(normal * 2 * (normal.dot(eyeDir)) - eyeDir);
      ngl::Vec3 halfVec(lightDir + eyeDir);

      lightDir.normalize();
      eyeDir.normalize();
      reflectDir.normalize();
      halfVec.normalize();

      float NdotH = std::max(0.0f, (float)normal.dot(halfVec));
      float NdotL = std::max(0.0f, (float)normal.dot(lightDir));

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

ngl::Colour RenderTask::renderPixel(std::vector<ngl::Vec2> _pixelSample)
{
  ngl::Colour outCol;
  for (auto p: _pixelSample){
    Ray newRay;
    m_cam->generateRay(p[0], p[1], &newRay);
    outCol = outCol + traceRay(newRay);
  }
  outCol *= (1/_pixelSample.size());
  return outCol;
}

ngl::Colour RenderTask::traceRay(const Ray &_ray)
{
  ngl::Colour outCol(0, 0, 0, 1);
  IsectData isect;
  if (m_scene->intersect(_ray, &isect)){

    ngl::Colour reflectedCol(0, 0, 0, 1);
    ngl::Colour refractedCol(0, 0, 0, 1);


    float n1 = 1;
    float n2 = 1;

    //air -> geometry boundary
    if (isect.m_eyeDir.dot(isect.m_n) < 0){
      //std::cout << "b" << std::endl;
      n2 = isect.m_material->m_f0;
    }
    //geometry -> air boundary
    else{
      //std::cout << "a" << std::endl;
      n1 = isect.m_material->m_f0;
      isect.m_n = -isect.m_n;
    }

    float reflectedAmount = rShclick(isect.m_n, isect.m_eyeDir, n1, n2);

    if (_ray.m_depth < 4){
      if (isect.m_material->m_isReflective){
        ngl::Vec3 reflectedDir(reflect(isect.m_n, isect.m_eyeDir));
        Ray reflectedRay(isect.m_pos + 0.0001 * reflectedDir, reflectedDir, _ray.m_depth + 1);
        reflectedCol = traceRay(reflectedRay);
      }
      else reflectedAmount = 0;
      //std::cout << reflectedCol.m_r << std::endl;
      if (isect.m_material->m_isTransparent){
        ngl::Vec3 refractedDir(refract(isect.m_n, isect.m_eyeDir, n1, n2));
        //check for tir
        //refractedDir.normalize();
        if (refractedDir != ngl::Vec3(0, 0, 0)){
          Ray refractedRay(isect.m_pos + 0.0001 * refractedDir, refractedDir, _ray.m_depth + 1);
          refractedCol = traceRay(refractedRay);
        }
        //std::cout << refractedCol.m_r << std::endl;
      }
      else{
        refractedCol = colourPixel(&isect);
      }
    }
    else{
      refractedCol = colourPixel(&isect);
    }

    //refractive calculations

    outCol = refractedCol * (1 - reflectedAmount) + reflectedCol * reflectedAmount;

  }
  return outCol;
}

ngl::Vec3 RenderTask::reflect(const ngl::Vec3 _n, const ngl::Vec3 _i)
{
  //http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
  float cosI = -_n.dot(_i);
  return _i + _n * 2 * cosI;
}

ngl::Vec3 RenderTask::refract(const ngl::Vec3 _n, const ngl::Vec3 _i, float _n1, float _n2)
{
  //http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
  float n = _n1/_n2;
  float cosI = -_n.dot(_i);
  float sinT2 = n * n * (1.0 - cosI * cosI);
  if (sinT2 > 1.0){
    return ngl::Vec3(0, 0, 0); // total internal reflection
  }
  float cosT = sqrt(1.0 - sinT2);
  return n * _i + (n * cosI - cosT) * _n;
  //std::cout << out << std::endl;
  //return out;
}

float RenderTask::rShclick(const ngl::Vec3 _n, const ngl::Vec3 _i, float _n1, float _n2)
{
  float r0 = (_n1 - _n2) / (_n1 + _n2);
  r0 *= r0;
  float cosI = -_n.dot(_i);
  if (_n1 > _n2){
    double n = _n1 / _n2;
    double sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0){
      return 1.0; // TIR
    }
    cosI = sqrt(1.0 - sinT2);
  }
  float x = 1.0 - cosI;
  float schlick =  r0 + (1.0 - r0) * x * x * x * x * x;
  if (schlick > .999) return 1;
  return schlick;
}



