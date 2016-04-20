#ifndef RENDERSETTINGS_HPP
#define RENDERSETTINGS_HPP

#include <iostream>
#include "QObject"
#include "QString"
#include "ngl/Colour.h"
#include "ngl/Vec3.h"

/// @file RenderSettings.hpp
/// @brief File contaiing the RenderSettings structure
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 09/04/2016

/// @struct RenderSeettings
/// @brief the render settings holds all of the settings that can be changed throgh the
/// ui. It inherits from qobject so that it can have slots and interface with the ui
struct RenderSettings: public QObject
{
  Q_OBJECT
public:
  /// @brief ctor that sets a default parent to 0
  /// @param [in] *_parent is the parent qobject, a system that qt uses for garbage collection of ui elements
  RenderSettings(QObject *_parent = 0){}

  void setTotalTasks(int _totalTasks){ emit totalTasksChanged(_totalTasks); }
  void addcompleteTask(){ m_completedTasks++; emit taskCompleted(m_completedTasks); }

  /// @brief renderers background colour
  ngl::Colour m_bgCol = ngl::Colour(0, 0, 0);

  /// @brief ambient lighting colour
  ngl::Colour m_ambientCol = ngl::Colour(0.2, 0.2, 0.2);

  /// @brief amount of anti aliasing samples to take
  float m_aaAmount = 1;

  /// @brief the render cameras position
  ngl::Vec3 m_camPos = ngl::Vec3(0, 0, 0);

  /// @brief the render cameras target vector
  ngl::Vec3 m_camTarget = ngl::Vec3(0, 0, 1);

  /// @brief the render cameras up vector
  ngl::Vec3 m_camUp = ngl::Vec3(0, 1, 0);

  /// @brief cameras field of view in degrees
  float m_fov = 80;

  /// @brief width of the output image in pixels
  int m_filmWidth = 1280;

  /// @brief height of the output image in pixels
  int m_filmHeight = 720;

  /// @brief maximun number of ray bounces
  int m_maxRayBounces = 3;

  /// @brief a bool to tell the renderer to multithread the rendering
  bool m_multithread = 1;

  /// @brief pixel width of a renderign thread
  int m_threadWidth = 32;

  /// @brief pixel height of a rendering thread
  int m_threadHeight = 32;

  /// @brief the scene text file path
  QString m_sceneFilePath;

  int m_totalThreads = 920;

  int m_completedTasks = 0;

public slots:
  //colour and lighting
  /// @brief slot that sets the background colour's red channel
  /// @param [in] _r is the value to be passed to the background colour's red value
  void setBGColourR(double _r){m_bgCol.m_r = _r;}

  /// @brief slot that sets the background colour's green channel
  /// @param [in] _g is the value to be passed to the background colour's green value
  void setBGColourG(double _g){m_bgCol.m_g = _g;}

  /// @brief slot that sets the background colour's blue channel
  /// @param [in] _b is the value to be passed to the background colour's blue value
  void setBGColourB(double _b){m_bgCol.m_b = _b;}

  /// @brief slot that sets the ambient colour's red channel
  /// @param [in] _r is the value to be passed to the ambient colour's red value
  void setAmbientColourR(double _r){m_ambientCol.m_r = _r;}

  /// @brief slot that sets the ambient colour's green channel
  /// @param [in] _g is the value to be passed to the ambient colour's green value
  void setAmbientColourG(double _g){m_ambientCol.m_g = _g;}

  /// @brief slot that sets the ambient colour's blue channel
  /// @param [in] _b is the value to be passed to the ambient colour's blue value
  void setAmbientColourB(double _b){m_ambientCol.m_b = _b;}

  //rendering
  /// @brief slot that sets the amount of anti aliasing to be used
  /// @param [in] _aaAmount is the amount of aa to be used
  void setAAAmount(int _aaAmount){m_aaAmount = _aaAmount;}

  /// @brief slot that sets the maximum number of ray bounces
  /// @param [in] _n is the maximum nimber of ray bounces
  void setMaxRayBounces(int _n){m_maxRayBounces = _n;}

  //cam settings
  /// @brief slot that sets the cameras x position
  /// @param [in] _x is the x value to be set
  void setCamPosX(double _x){m_camPos.m_x = _x;}

  /// @brief slot that sets the cameras y position
  /// @param [in] _y is the y value to be set
  void setCamPosY(double _y){m_camPos.m_y = _y;}

  /// @brief slot that sets the cameras z position
  /// @param [in] _z is the z value to be set
  void setCamPosZ(double _z){m_camPos.m_z = _z;}

  /// @brief slot that sets the cameras target x position
  /// @param [in] _x is the x value to be set
  void setCamTargetX(double _x){m_camTarget.m_x = _x;}

  /// @brief slot that sets the cameras target y position
  /// @param [in] _y is the y value to be set
  void setCamTargetY(double _y){m_camTarget.m_y = _y;}

  /// @brief slot that sets the cameras target z position
  /// @param [in] _z is the z value to be set
  void setCamTargetZ(double _z){m_camTarget.m_z = _z;}

  /// @brief slot that sets the cameras up vectors x value
  /// @param [in] _x is the x value to be set
  void setCamUpX(double _x){m_camUp.m_x = _x;}

  /// @brief slot that sets the cameras up vectors y value
  /// @param [in] _y is the y value to be set
  void setCamUpY(double _y){m_camUp.m_y = _y;}

  /// @brief slot that sets the cameras up vectors z value
  /// @param [in] _z is the z value to be set
  void setCamUpZ(double _z){m_camUp.m_z = _z;}

  /// @brief slot that sets the cameras fov
  /// @param [in] _fov is the fov to be set
  void setFOV(double _fov){m_fov = _fov;}

  /// @brief slot that sets the film width in pixels
  /// @param [in] _w is the width value to be set
  void setFilmWidth(int _w){m_filmWidth = _w;}

  /// @brief slot that sets the film height in pixels
  /// @param [in] _h is the height value to be set
  void setFilmHeight(int _h){m_filmHeight = _h;}
  //multithreading

  /// @brief slot that sets the multiThread bool
  /// @param [in] _b is the boolean value to be set
  void setMultithread(bool _b){m_multithread = _b;}

  /// @brief slot that sets the width in pixels of each thread
  /// @param [in] _w is the width value to be set
  void setThreadWidth(int _w){m_threadWidth = _w;}

  /// @brief slot that sets the height in pixels of each thread
  /// @param [in] _h is the height value to be set
  void setThreadHeight(int _h){m_threadHeight = _h;}

  /// @brief slot that sets the path to the scene file
  /// @param [in] _path is the string to be passed in
  void setScenePath(QString _path){m_sceneFilePath = _path;}

signals:
    void totalTasksChanged(int _totalTasks);
    void taskCompleted(int _completedTasks);
};

#endif//RENDERSETTINGS_HPP
