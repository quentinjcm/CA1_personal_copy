#ifndef __BRDF_HPP__
#define __BRDF_HPP__

#include <ngl/Vec3.h>

class BRDF
{
public:

private:
  double fresnel(ngl::Vec3 _l, ngl::Vec3 _n);


  double m_IOR;
  double m_f0;
};

#endif//__BRDF_HPP__
