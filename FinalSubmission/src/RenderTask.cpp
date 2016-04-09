#include <memory>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <ngl/NGLStream.h>
#include <ngl/Colour.h>


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
                       std::shared_ptr<RenderSettings> _settings):
  m_cam(_cam),
  m_film(_film),
  m_scene(_scene),
  m_xMin(_xMin),
  m_yMin(_yMin),
  m_xMax(_xMax),
  m_yMax(_yMax),
  m_settings(_settings)
{
}

void RenderTask::render()
{
  for (int x = m_xMin; x < m_xMax; x++){
    for (int y = m_yMin; y < m_yMax; y++){
      std::vector<ngl::Vec2> samples;
      //use aa value to generate samples
      samples.push_back(ngl::Vec2(x, y));
      m_film->setPixel(x, y, renderPixel(samples));
    }
  }
}

ngl::Colour RenderTask::blinPixel(IsectData *_intersection)
{
  ngl::Colour outColour(0, 0, 0, 1);
  ngl::Colour matColour = _intersection->m_material->getDiffuseColour(_intersection->m_uv[0],
                                                                      _intersection->m_uv[1]);

  //ambient lighting
  outColour += m_settings->m_ambientCol * matColour; //ambient

  for (Light &l: m_scene->m_sceneLights){
    if(isVisible(_intersection->m_pos, l.m_pos)){
      ngl::Vec3 normal(_intersection->m_n);
      ngl::Vec3 lightDir(l.m_pos - _intersection->m_pos);
      double lightDist = lightDir.length();
      double attenuation = 1.0 / (1.0 + 0.1 * lightDist + 0.01 * lightDist * lightDist);
      ngl::Vec3 eyeDir(_intersection->m_eyeDir);
      ngl::Vec3 reflectDir(normal * 2 * (normal.dot(eyeDir)) - eyeDir);
      ngl::Vec3 halfVec(lightDir + eyeDir);

      lightDir.normalize();
      eyeDir.normalize();
      reflectDir.normalize();
      halfVec.normalize();

      double NdotH = std::max(0.0, (double)normal.dot(halfVec));
      double NdotL = std::max(0.0, (double)normal.dot(lightDir));

      outColour += (l.m_colour * std::pow(NdotH, _intersection->m_material->m_smoothness) * attenuation * l.m_intensity); //specular
      outColour += l.m_colour * NdotL * NdotL * matColour * attenuation * l.m_intensity; //diffuse
    }
  }
  outColour.clamp(0, 1);
  return outColour;
}

bool RenderTask::isVisible(ngl::Vec3 _point, ngl::Vec3 _lightPos)
{
  ngl::Vec3 direction(_lightPos - _point);
  _point += direction*0.001;
  Ray shadowRay(_point, direction);
  shadowRay.m_maxT = 1;
  IsectData dummy;
  if (m_scene->sIntersect(shadowRay)){
    return false;
  }
  return true;
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
  ngl::Colour outCol = m_settings->m_bgCol;
  IsectData isect;
  if (m_scene->intersect(_ray, &isect)){

    ngl::Colour reflectedCol(0, 0, 0, 1);
    ngl::Colour refractedCol(0, 0, 0, 1);


    double n1 = 1;
    double n2 = 1;

    //air -> geometry boundary
    if (isect.m_eyeDir.dot(isect.m_n) < 0){
      //std::cout << "b" << std::endl;
      n2 = isect.m_material->m_ior;
    }
    //geometry -> air boundary
    else{
      //std::cout << "a" << std::endl;
      n1 = isect.m_material->m_ior;
      isect.m_n = -isect.m_n;
    }

    double reflectedAmount = rShclick(isect.m_n, isect.m_eyeDir, n1, n2);

    if (_ray.m_depth < m_settings->m_maxRayBounces){
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
        refractedCol = blinPixel(&isect);
      }
    }
    else{
      refractedCol = blinPixel(&isect);
    }

    //refractive calculations

    outCol = refractedCol * (1 - reflectedAmount) + reflectedCol * reflectedAmount;

  }
  return outCol;
}

ngl::Vec3 RenderTask::reflect(const ngl::Vec3 _n, const ngl::Vec3 _i)
{
  //http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
  double cosI = -_n.dot(_i);
  return _i + _n * 2 * cosI;
}

ngl::Vec3 RenderTask::refract(const ngl::Vec3 _n, const ngl::Vec3 _i, double _n1, double _n2)
{
  //http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
  double n = _n1/_n2;
  double cosI = -_n.dot(_i);
  double sinT2 = n * n * (1.0 - cosI * cosI);
  if (sinT2 > 1.0){
    return ngl::Vec3(0, 0, 0); // total internal reflection
  }
  double cosT = sqrt(1.0 - sinT2);
  return n * _i + (n * cosI - cosT) * _n;
  //std::cout << out << std::endl;
  //return out;
}

double RenderTask::rShclick(const ngl::Vec3 _n, const ngl::Vec3 _i, double _n1, double _n2)
{
  double r0 = (_n1 - _n2) / (_n1 + _n2);
  r0 *= r0;
  double cosI = -_n.dot(_i);
  if (_n1 > _n2){
    double n = _n1 / _n2;
    double sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0){
      return 1.0; // TIR
    }
    cosI = sqrt(1.0 - sinT2);
  }
  double x = 1.0 - cosI;
  double schlick =  r0 + (1.0 - r0) * x * x * x * x * x;
  if (schlick > .999) return 1;
  return schlick;
}



