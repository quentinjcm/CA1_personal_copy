#include <limits>

#include "IsectData.hpp"

IsectData::IsectData():
  m_t(std::numeric_limits<double>::infinity()),
  m_pos(0.0, 0.0, 0.0),
  m_material(nullptr)
{
}
