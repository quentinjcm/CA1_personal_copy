#include <memory>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include<chrono>
#include <ngl/NGLStream.h>
#include <ngl/Colour.h>
#include "RenderTask.hpp"
#include "Film.hpp"
#include "Camera.hpp"
#include "Primative.hpp"
#include "Material.hpp"

/// @file RenderTask.cpp
/// @brief implementation file for the RenderTask class

RenderTask::RenderTask(Camera *_cam,
                       Film *_film,
                       std::shared_ptr<Scene> _scene,
                       int _xMin, int _yMin,
                       int _xMax, int _yMax,
                       std::shared_ptr<RenderSettings> _settings):
  m_cam(_cam),
  m_film(_film),
  m_scene(_scene),
  m_settings(_settings),
  m_xMin(_xMin),
  m_yMin(_yMin),
  m_xMax(_xMax),
  m_yMax(_yMax)
{
  //setting up the random number generator for random sampling
  m_generator = std::mt19937(std::random_device{}());
  m_distribution =  std::uniform_real_distribution<double>(-0.5, 0.5);
}

void RenderTask::render()
{
  //runs through each pixel in the task
  for (int x = m_xMin; x < m_xMax; x++)
  {
    for (int y = m_yMin; y < m_yMax; y++)
    {
      //generating aa samples for the pixel
      std::vector<ngl::Vec2> samples;
      if (m_settings->m_aaAmount > 1)
      {
        generateAASamples(x, y, &samples);
      }
      else
      {
        samples.push_back(ngl::Vec2(x, y));
      }
      //rendering the pixel, with the given samples
      m_film->setPixel(x, y, renderPixel(samples));
    }
  }
}

ngl::Colour RenderTask::blinnPixel(IsectData *_intersection)
{
  ngl::Colour outColour(0, 0, 0, 1);
  ngl::Colour matColour = _intersection->m_material->getDiffuseColour(_intersection->m_uv[0],
                                                                      _intersection->m_uv[1]);

  //ambient lighting
  outColour += m_settings->m_ambientCol * matColour;

  //after ambien colour, each lights contribution to the specular and diffuse terms are calulated
  for (Light &l: *m_scene->getLights())
  {
    // if the light is visible, its contribution to the point is calculated
    if(isVisible(_intersection->m_pos, l.m_pos))
    {

      // setting up lighting variables
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

      // specular lighting
      outColour += (l.m_colour * std::pow(NdotH, _intersection->m_material->m_smoothness) * attenuation * l.m_intensity);
      // diffuse lighting
      outColour += l.m_colour * NdotL * matColour * attenuation * l.m_intensity;
    }
  }
  // clamping the colour that goes to the display
  outColour.clamp(0, 1);
  return outColour;
}

bool RenderTask::isVisible(ngl::Vec3 _point, ngl::Vec3 _lightPos)
{
  // direction from intersection to light
  ngl::Vec3 direction(_lightPos - _point);
  // offset the position so that there are no intersections with the surface it is bouncing off
  _point += direction*0.001;
  Ray shadowRay(_point, direction);
  // because i dont normalise the vector betwen the light and the point, at t = 1 is when it has reached the light
  shadowRay.m_maxT = 1;
  if (m_scene->sIntersect(shadowRay))
  {
    return false;
  }
  return true;
}

ngl::Colour RenderTask::renderPixel(std::vector<ngl::Vec2> _pixelSample)
{
  // renders each of the samples and averages the results
  ngl::Colour outCol;
  for (auto p: _pixelSample)
  {
    // generate and trace a ray for each sampls
    Ray newRay;
    m_cam->generateRay(p[0], p[1], &newRay);
    outCol = outCol + traceRay(newRay);
  }
  // averaging the output colour
  outCol *= (1.0/_pixelSample.size());
  return outCol;
}

ngl::Colour RenderTask::traceRay(const Ray &_ray)
{
  // setting the colour to the background colour, in case no intersections are found
  ngl::Colour outCol(m_settings->m_bgCol);
  IsectData isect;

  // intersect the scene with the ray
  if (m_scene->intersect(_ray, &isect))
  {
    //init reflected and refracted colour
    ngl::Colour reflectedCol(m_settings->m_bgCol);
    ngl::Colour refractedCol(m_settings->m_bgCol);


    // refractive indicies of materials, n1 is current material, n2 is new material
    double n1 = 1;
    double n2 = 1;

    // using the interpolated normal and eye direction to find out what side of the boundary on
    // assumes all normals point outwards (which they do for my  procedural meshes and
    // it is on the used to ensure their objs are good
    // air -> geometry boundary
    if (isect.m_eyeDir.dot(isect.m_n) < 0)
    {
      n2 = isect.m_material->m_ior;
    }
    // geometry -> air boundary
    else
    {
      // reverse the normal if the ray is coming out
      n1 = isect.m_material->m_ior;
      isect.m_n = -isect.m_n;
    }

    // using the shlick approximation to find out how much light is reflected (the rest is refracted)
    double reflectedAmount = rShclick(isect.m_n, isect.m_eyeDir, n1, n2);

    if (_ray.m_depth < m_settings->m_maxRayBounces)
    {
      if (isect.m_material->m_isReflective)
      {
        ngl::Vec3 reflectedDir(reflect(isect.m_n, isect.m_eyeDir));
        Ray reflectedRay(isect.m_pos + 0.0001 * reflectedDir, reflectedDir, _ray.m_depth + 1);
        reflectedCol = traceRay(reflectedRay);
      }
      else reflectedAmount = 0;
      //std::cout << reflectedCol.m_r << std::endl;
      if (isect.m_material->m_isTransparent)
      {
        ngl::Vec3 refractedDir(refract(isect.m_n, isect.m_eyeDir, n1, n2));
        //check for tir
        if (refractedDir != ngl::Vec3(0, 0, 0))
        {
          Ray refractedRay(isect.m_pos + 0.0001 * refractedDir, refractedDir, _ray.m_depth + 1);
          refractedCol = traceRay(refractedRay);
        }
      }
      // default refracted amout to blinn shading if material is not transparent
      else
      {
        refractedCol = blinnPixel(&isect);
      }
    }
    // default to blinn shading if max ray bounces have been reached
    else
    {
      refractedCol = blinnPixel(&isect);
      reflectedAmount = 0;
    }
    //refractive calculations
    outCol = refractedCol * (1 - reflectedAmount) + reflectedCol * reflectedAmount;
  }
  return outCol;
}

ngl::Vec3 RenderTask::reflect(const ngl::Vec3 _normal, const ngl::Vec3 _incident)
{
  /* calulating the reflected direction of a ray using examples from:
   * http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
   */
  // angle between incident and normal
  // negative because the incident vector is coming towards the point and needs to be reversed
  double cosI = _normal.dot(-_incident);
  return _incident + _normal * 2 * cosI;
}

ngl::Vec3 RenderTask::refract(const ngl::Vec3 _normal, const ngl::Vec3 _incident, double _n1, double _n2)
{
  /* calulating the reflected direction of a ray using examples from:
   * http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
   */
  double n = _n1/_n2;
  double cosI = -_normal.dot(_incident);
  double sinT2 = n * n * (1.0 - cosI * cosI);
  if (sinT2 > 1.0)
  {
    return ngl::Vec3(0, 0, 0); // total internal reflection
  }
  double cosT = sqrt(1.0 - sinT2);
  return n * _incident + (n * cosI - cosT) * _normal;

}

double RenderTask::rShclick(const ngl::Vec3 _normal, const ngl::Vec3 _incident, double _n1, double _n2)
{
  /* calculating the fresnel factor using schlicks approximation, code and explnation can be found at:
   * http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
   */
  double r0 = (_n1 - _n2) / (_n1 + _n2);
  r0 *= r0;
  double cosI = _normal.dot(-_incident);
  if (_n1 > _n2)
  {
    double n = _n1 / _n2;
    double sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0)
    {
      // total internal reflection
      return 1.0;
    }
    cosI = sqrt(1.0 - sinT2);
  }
  double x = 1.0 - cosI;
  double schlick =  r0 + (1.0 - r0) * x * x * x * x * x;
  // "fixing" an odd rounding error
  if (schlick > .999) return 1;
  return schlick;
}

void RenderTask::generateAASamples(const int _x, const int _y, std::vector<ngl::Vec2> *_samples)
{
  // random number generator to generate random samples
  for (int i = 0; i < m_settings->m_aaAmount; i++)
  {
    double x = m_distribution(m_generator) + (double)_x;
    double y = m_distribution(m_generator) + (double)_y;
    _samples->push_back(ngl::Vec2(x, y));
  }
}



