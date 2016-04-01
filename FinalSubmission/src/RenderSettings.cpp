
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include "RenderSettings.hpp"

RenderSettings::RenderSettings(QObject *_parent)
{

}

void RenderSettings::printSettings()
{
  std::cout << "m_bgCol red = " << m_bgCol.m_r << std::endl;
  std::cout << "m_ambientCol red = " << m_ambientCol.m_r << std::endl;
  std::cout << "m_ambientIntensity = " << m_ambientIntensity << std::endl;
  std::cout << "m_aaType = " << m_aaType << std::endl;
  std::cout << "m_aaAmount = " << m_aaAmount << std::endl;
  std::cout << "m_camPos = " << m_camPos << std::endl;
  std::cout << "m_camAim = " << m_camAim << std::endl;
  std::cout << "m_camUp = " << m_camUp << std::endl;
  std::cout << "m_fov = " << m_fov << std::endl;
  std::cout << "m_filmWidth = " << m_filmWidth << std::endl;
  std::cout << "m_filmHeight = " << m_filmHeight << std::endl;
  std::cout << "m_maxRayBounces = " << m_maxRayBounces << std::endl;
  std::cout << "m_multithread = " << m_multithread << std::endl;
  std::cout << "m_threadWidth = " << m_threadWidth << std::endl;
  std::cout << "m_threadHeight = " << m_threadHeight << std::endl;
  std::cout << "file path = " << m_filePath.toStdString() << std::endl;
}
