#ifndef CAMERA_HPP__
#define CAMERA_HPP__

#include "ngl/Vec3.h"
#include "ngl/Vec4.h"
#include "ngl/Mat4.h"
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
/// @brief The Camera class is used to generate rays when passed the coordinate of a point in the output image
class Camera
{
public:
  Camera() = default;

  /// @brief ctor that builds the transformtion matricies to move from camera to world space
  /// @param [in] _pos is the position of the camera in world space
  /// @param [in] _lookAt is a point in world space that the camera will look at
  /// @param [in] _up is a vector that indicated the world space direction of up for the camera
  /// @param [in] _fov is an angle in degrees that sets the field of view for the camera, not currently implemented
  /// @param [in] _filmWidth is the width of the output image in pixels
  /// @param [in] _filmHeight is the height of the output image in pixels
  Camera(ngl::Vec3 _pos,
         ngl::Vec3 _lookAt,
         ngl::Vec3 _up,
         double _fov,
         int _filmWidth,
         int _filmHeight);

  /// @brief fills the ray with an origin and direction corresponding to the x, y pixel on the final image
  /// @param [in] _x is the x pixel of the final image
  /// @param [in] _y is the y pixel of the final image
  /// @param [in] *_ray is the ray to be filled up with data
  void generateRay(double _x, double _y, Ray *_ray) const;

private:
  /// @brief width of the output image
  int m_screenWidth;

  /// @brief height of the output image
  int m_screenHeight;

  /// @brief aspect ratio of the screen
  double m_aspectRatio;

  /// @brief a rotation matrix that moves a vector in camera space to world space
  ngl::Mat4 m_rotate;

  /// @brief a rotationMatrix that moves a pointdefined in camrea space to world space
  ngl::Mat4 m_camToWorld;

  /// @brief field of view for the camera
  double m_fovMult;
};

#endif  // end of CAMERA_HPP__
