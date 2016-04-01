#ifndef RENDERSETTINGS_HPP
#define RENDERSETTINGS_HPP

#include <QObject>
#include <QString>

#include <ngl/Colour.h>
#include <ngl/Vec3.h>

class RenderSettings: public QObject
{
  Q_OBJECT

public:

  RenderSettings(QObject *_parent = 0);
  ~RenderSettings() = default;

  ngl::Colour m_bgCol = ngl::Colour(0, 0, 0);
  ngl::Colour m_ambientCol = ngl::Colour(0, 0, 0);
  float m_ambientIntensity = 10;
  float m_aaType = 0;
  float m_aaAmount = 0;
  ngl::Vec3 m_camPos = ngl::Vec3(0, 0, 0);
  ngl::Vec3 m_camAim = ngl::Vec3(0, 0, 1);
  ngl::Vec3 m_camUp = ngl::Vec3(0, 1, 0);
  float m_fov = 80;
  int m_filmWidth = 1280;
  int m_filmHeight = 720;
  int m_maxRayBounces = 3;
  bool m_multithread = 1;
  int m_threadWidth = 32;
  int m_threadHeight = 32;
  QString m_filePath;

public slots:
  //colour and lighting
  void setBGColourR(double _r){m_bgCol.m_r = _r;}
  void setBGColourG(double _g){m_bgCol.m_g = _g;}
  void setBGColourB(double _b){m_bgCol.m_b = _b;}
  void setAmbientColourR(double _r){m_ambientCol.m_r = _r;}
  void setAmbientColourG(double _g){m_ambientCol.m_g = _g;}
  void setAmbientColourB(double _b){m_ambientCol.m_b = _b;}
  void setAmbientIntensity(double _i){m_ambientIntensity = _i;}
  //rendering
  void setAAType(int _aaType){m_aaType = _aaType;}
  void setAAAmount(int _aaAmount){m_aaType = _aaAmount;}
  void setMaxRayBounces(int _n){m_maxRayBounces = _n;}
  //cam settings
  void setCamPosX(double _x){m_camPos.m_x = _x;}
  void setCamPosY(double _y){m_camPos.m_y = _y;}
  void setCamPosZ(double _z){m_camPos.m_z = _z;}
  void setCamAimX(double _x){m_camAim.m_x = _x;}
  void setCamAimY(double _y){m_camAim.m_y = _y;}
  void setCamAimZ(double _z){m_camAim.m_z = _z;}
  void setCamUpX(double _x){m_camUp.m_x = _x;}
  void setCamUpY(double _y){m_camUp.m_y = _y;}
  void setCamUpZ(double _z){m_camUp.m_z = _z;}
  void setFOV(double _fov){m_fov = _fov;}
  void setFilmWidth(int _w){m_filmWidth = _w;}
  void setFilmHeight(int _h){m_filmHeight = _h;}
  //multithreading
  void setMultithread(bool _b){m_multithread = _b;}
  void setThreadWidth(int _w){m_threadWidth = _w;}
  void setThreadHeight(int _h){m_threadHeight = _h;}
  void setScenePath(QString _path){m_filePath = _path;}

  void printSettings();
};

#endif//__RENDERSETTINGS_HPP__
