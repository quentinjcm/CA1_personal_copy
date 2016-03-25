#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Mat4.h>

#include "Ray.hpp"
#include "Film.hpp"

#ifndef M_PI
  #define M_PI 3.14159265
#endif

/// @file Camera.hpp
/// @brief File contaiing the Camera class
/// @author Quentin Corker-Marin
/// @version 1.0
/// @date 12/03/2016
/// @class Camera
/// @brief The Camera class is used to generate rays when passed a pixel value as x, y

class Camera
{
public:
  /// @brief ctor that builds the transformtion matricies to move from camera to world space
  /// @param [in] _pos is the position of the camera in world space
  /// @param [in] _lookAt is a point in world space that the camera will look at
  /// @param [in] _up is a vector that indicated the world space direction of up for the camera
  /// @param [in] _fov is an angle in degrees that sets the field of view for the camera, not currently implemented
  /// @param [in] *_film is where the final image output will be stored, it contains data on the width and height of the image
  /// will probably extract width and height and store them inside the class
  Camera(ngl::Vec3 _pos,
         ngl::Vec3 _lookAt,
         ngl::Vec3 _up,
         float _fov,
         Film *_film);

  /// @brief fills the ray with an origin and direction corresponding to the x, y pixel on the final image
  /// @param [in] _x is the x pixel of the final image
  /// @param [in] _y is the y pixel of the final image
  /// @param [in] *_ray is the ray to be filled up with data
  void generateRay(float _x, float _y, Ray *_ray);

private:
  /// @brief width of the output image
  int m_screenWidth;

  /// @brief height of the output image
  int m_screenHeight;

  /// @brief aspect ratio of the screen
  float m_aspectRatio;

  /// @brief a rotation matrix that moves a vector in camera space to world space
  ngl::Mat4 m_rotate;

  /// @brief a rotationMatrix that moves a pointdefined in camrea space to world space
  ngl::Mat4 m_camToWorld;

  /// @brief field of view for the camera
  float m_fovMult;
};

#endif//__CAMERA_HPP__
