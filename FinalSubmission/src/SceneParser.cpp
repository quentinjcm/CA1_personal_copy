/*
public:
  SceneParser(std::string _fileName);
  void parseScene();
  void parseSphere(const char *_begin);
  void parsePlane(const char *_begin);
  void parseObj(const char *_begin);
  void parseMat(const char *_begin);
private:
  std::shared_ptr<Scene> m_scene;
  std::string m_fileName;
*/

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

#include <boost/bind.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/foreach.hpp>

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <ngl/NGLStream.h>
#include <ngl/Obj.h>

#include "SceneParser.hpp"
#include "Scene.hpp"
#include "Meshes.hpp"
#include "GeometricPrim.hpp"
#include "Light.hpp"

//borrowed from jon
namespace spt = boost::spirit::classic;
typedef spt::rule<spt::phrase_scanner_t> srule;

SceneParser::SceneParser(std::string _fileName, std::shared_ptr<Scene> _scene):
  m_scene(_scene),
  m_fileName(_fileName)
{
  m_currentMat = std::make_shared<Material>();
  m_currentMat->m_diffuseColour = ngl::Colour(0.5, 0.5, 0.5);
  m_currentMat->m_smoothness = 20;
  m_currentMat->m_f0 = 0.3;
}

void SceneParser::parseSphere(const char *_begin)
{
  ngl::Vec3 pos(0, 0, 0);
  float radius = 0;
  int divisions = 4;

  srule sphere = "SPHERE:" >>
                 spt::real_p[spt::assign_a(pos[0])] >>
                 spt::real_p[spt::assign_a(pos[1])] >>
                 spt::real_p[spt::assign_a(pos[2])] >>
                 spt::int_p[spt::assign_a(divisions)] >>
                 spt::real_p[spt::assign_a(radius)];

  spt::parse(_begin, sphere, spt::space_p);
  std::cout << "creating prim " << radius << ", " << divisions << std::endl;
  auto prim = std::make_shared<GeometricPrim>(Meshes::pSphere(radius, divisions), m_currentMat);
  m_scene->addPrim(prim);
}

void SceneParser::parsePlane(const char *_begin)
{
  ngl::Vec3 pos(0, 0, 0);
  float width = 1;
  float height = 1;

  srule plane = "PLANE:" >>
                spt::real_p[spt::assign_a(pos[0])] >>
                spt::real_p[spt::assign_a(pos[1])] >>
                spt::real_p[spt::assign_a(pos[2])] >>
                spt::real_p[spt::assign_a(width)] >>
                spt::real_p[spt::assign_a(height)];

  spt::parse(_begin, plane, spt::space_p);
  auto prim = std::make_shared<GeometricPrim>(Meshes::pPlane(width, height), m_currentMat);
  m_scene->addPrim(prim);
}

void SceneParser::parseObj(const char *_begin)
{
  std::string fileName;

  srule obj = "OBJ:" >>
               (*(+spt::alnum_p >> "/") >>
               +spt::alnum_p >> ".obj")[spt::assign_a(fileName)];

  spt::parse(_begin, obj, spt::space_p);

  ngl::Obj objMesh(fileName);




  std::cout << "obj created from file " << fileName << std::endl;
}

void SceneParser::parseMat(const char *_begin)
{
  ngl::Colour colour(0, 0, 0, 1);
  int smoothness = 0;
  //float reflectivity = 0;
  float IOR = 0;
  std::string texFile;
  srule mat = "MAT:" >>
              spt::real_p[spt::assign_a(colour.m_r)] >>
              spt::real_p[spt::assign_a(colour.m_g)] >>
              spt::real_p[spt::assign_a(colour.m_b)] >>
              spt::int_p[spt::assign_a(smoothness)] >>
              spt::real_p[spt::assign_a(IOR)] >>
              (*(+spt::alnum_p >> "/") >>
              +spt::alnum_p >> "." >> +spt::alnum_p)[spt::assign_a(texFile)];

  spt::parse(_begin, mat, spt::space_p);
  m_currentMat = std::make_shared<Material>(colour, smoothness, IOR, texFile);
}

void SceneParser::parseLight(const char *_begin)
{
  ngl::Colour colour(0, 0, 0);
  ngl::Vec3 pos(0, 0, 0);
  float intensity;

  srule light = "LIGHT:" >>
                spt::real_p[spt::assign_a(pos[0])] >>
                spt::real_p[spt::assign_a(pos[1])] >>
                spt::real_p[spt::assign_a(pos[2])] >>
                spt::real_p[spt::assign_a(colour.m_r)] >>
                spt::real_p[spt::assign_a(colour.m_g)] >>
                spt::real_p[spt::assign_a(colour.m_b)] >>
                spt::real_p[spt::assign_a(intensity)];

  spt::parse(_begin, light, spt::space_p);
  m_scene->addLight(Light(pos, colour, intensity));
}

void SceneParser::parseScene()
{
  srule comment = spt::comment_p("#");
  srule sphere = ("SPHERE:" >>
                  spt::real_p >>
                  spt::real_p >>
                  spt::real_p >>
                  spt::int_p >>
                  spt::real_p)
                  [bind(&SceneParser::parseSphere, boost::ref(*this), _1)];
  srule plane = ("PLANE:" >>
                 spt::real_p >>
                 spt::real_p >>
                 spt::real_p >>
                 spt::real_p >>
                 spt::real_p)
                 [bind(&SceneParser::parsePlane, boost::ref(*this), _1)];
  srule obj = ("OBJ:" >>
               *(+spt::alnum_p >> "/") >>
               +spt::alnum_p >> ".obj")
               [bind(&SceneParser::parseObj, boost::ref(*this), _1)];
  srule mat = ("MAT:" >>
               spt::real_p >>
               spt::real_p >>
               spt::real_p >>
               spt::int_p >>
               spt::real_p >>
               *(+spt::alnum_p >> "/") >>
               (+spt::alnum_p) >> "." >> (+spt::alnum_p))
               [bind(&SceneParser::parseMat, boost::ref(*this), _1)];
  srule light = ("LIGHT:" >>
                spt::real_p >>
                spt::real_p >>
                spt::real_p >>
                spt::real_p >>
                spt::real_p >>
                spt::real_p >>
                spt::real_p)
                [bind(&SceneParser::parseLight, boost::ref(*this), _1)];

  std::ifstream fileIn(m_fileName.c_str());
  if (fileIn.is_open()){
    std::string line;
    while (std::getline(fileIn, line)){
      spt::parse(line.c_str(), comment | sphere | plane | obj | mat | light, spt::space_p);
    }
  }
}
