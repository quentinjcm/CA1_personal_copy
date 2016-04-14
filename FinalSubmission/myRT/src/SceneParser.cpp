#include <string>
#include <memory>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/spirit/include/classic.hpp>
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"
#include "ngl/Mat4.h"
#include "ngl/Mat3.h"
#include "ngl/Colour.h"
#include "ngl/Obj.h"
#include "ngl/NGLStream.h"
#include "SceneParser.hpp"
#include "Scene.hpp"
#include "ProceduralMeshes.hpp"
#include "GeometricPrim.hpp"
#include "Light.hpp"
#include "Triangle.hpp"

//taken from looking at the ngl::obj implementation
namespace spt = boost::spirit::classic;
typedef spt::rule<spt::phrase_scanner_t> srule;

SceneParser::SceneParser(std::string _fileName, std::shared_ptr<Scene> _scene):
  m_scene(_scene),
  m_fileName(_fileName)
{
  //building a default material
  m_currentMat = std::make_shared<Material>(ngl::Colour(.3, .3, .3), 10, 1.5, 0, 1, "textures/uvGrid.png");
}

void SceneParser::parseScene()
{
  /* the initial syntax checked for are operation names followed by a string of characters
   * the parser then goes through the input file line by line, and if any of these meet
   * the requirements of any of the defined rules, then that line is passed to the corresponding
   * function that will read the line and perform the required operations
   */
  //initial rules that define what function each line is passed to
  srule comment = spt::comment_p("#");
  srule sphere = ("SPHERE:" >> *(spt::anychar_p))
                  [bind(&SceneParser::parseSphere, boost::ref(*this), _1)];
  srule plane = ("PLANE:" >> *(spt::anychar_p))
                 [bind(&SceneParser::parsePlane, boost::ref(*this), _1)];
  srule obj = ("OBJ:" >> *(spt::anychar_p))
               [bind(&SceneParser::parseObj, boost::ref(*this), _1)];
  srule mat = ("MAT:" >> *(spt::anychar_p))
               [bind(&SceneParser::parseMat, boost::ref(*this), _1)];
  srule light = ("LIGHT:" >> *(spt::anychar_p))
                [bind(&SceneParser::parseLight, boost::ref(*this), _1)];
  srule translate = ("TRANSLATE:" >> *(spt::anychar_p))
                [bind(&SceneParser::parseTranslate, boost::ref(*this), _1)];
  srule rotate = ("ROTATE:" >> *(spt::anychar_p))
                [bind(&SceneParser::parseRotate, boost::ref(*this), _1)];

  // opens the specified file
  std::ifstream fileIn(m_fileName.c_str());

  // if it opened sucessfully it is paresd line by line
  if (fileIn.is_open()){
    std::string line;
    while (std::getline(fileIn, line)){
      // parsing the line according to the inital rules set above
      spt::parse(line.c_str(), comment | sphere | plane | obj | mat | light | rotate | translate, spt::space_p);
    }
    std::cout << "scene loaded" << std::endl;
  }
  else
  {
    std::cout << "scene  failed to load: \"" << m_fileName << "\"" << std::endl;
  }
}

void SceneParser::parseSphere(const char *_begin)
{
  // default values incase nothing is specified for the sphere
  double radius = 1;
  int divisions = 4;

  // assign the first number to the divions, and the second to the radius
  srule sphere = "SPHERE:" >>
                 spt::int_p[spt::assign_a(divisions)] >>
                 spt::real_p[spt::assign_a(radius)];

  // parse the line according to the rule just specified
  spt::parse(_begin, sphere, spt::space_p);

  // constructing the sphere
  auto prim = std::make_shared<GeometricPrim>(ProceduralMeshes::pSphere(radius, divisions, m_currentTransform), m_currentMat);

  // adding the sphere to the scene
  m_scene->addPrim(prim);
}

void SceneParser::parsePlane(const char *_begin)
{
  // default values for the plane
  double width = 1;
  double height = 1;

  // first number is the width, second is the height
  srule plane = "PLANE:" >>
                spt::real_p[spt::assign_a(width)] >>
                spt::real_p[spt::assign_a(height)];

  // parse the line according to the rule specified
  spt::parse(_begin, plane, spt::space_p);

  // constructing the plane
  auto prim = std::make_shared<GeometricPrim>(ProceduralMeshes::pPlane(width, height, m_currentTransform), m_currentMat);

  // adding the plane to the scene
  m_scene->addPrim(prim);
}

void SceneParser::parseObj(const char *_begin)
{
  std::string fileName;

  // the input file is a path, which is strings of alphanumeric characters seperated by /
  // the path is passed to the fileName
  srule obj = "OBJ:" >>
               (*(+spt::alnum_p >> "/") >>
               +spt::alnum_p >> ".obj")[spt::assign_a(fileName)];

  // line is paresd according to the rule above
  spt::parse(_begin, obj, spt::space_p);

  // using ngl::obj to read in and parse the obj
  ngl::Obj objMesh;

  // loading the obj
  objMesh.load(fileName, false);

  // if the mesh is triangular, then the data inside is translated into the format i wrote for the ray tracer
  if (objMesh.isTriangular()){

    //constructing the transform matricies for verts and normals
    ngl::Mat4 transform(m_currentTransform.getMatrix());
    ngl::Mat4 nTransform(transform);
    nTransform.inverse();

    auto meshOut = std::make_shared<TriangleMesh>();
    std::vector<ngl::Vec3> verts = objMesh.getVertexList();
    std::vector<ngl::Vec3> normals = objMesh.getNormalList();
    std::vector<ngl::Vec3> uvs = objMesh.getTextureCordList();
    std::vector<ngl::Face> faces = objMesh.getFaceList();
    for (ngl::Face f: faces){
      //converting uv cords from vec3 to vec2
      ngl::Vec2 uv0(uvs[f.m_tex[0]][0], uvs[f.m_tex[0]][1]);
      ngl::Vec2 uv1(uvs[f.m_tex[1]][0], uvs[f.m_tex[1]][1]);
      ngl::Vec2 uv2(uvs[f.m_tex[2]][0], uvs[f.m_tex[2]][1]);
      // extracting face data
      ngl::Vec3 v0(verts[f.m_vert[0]]);
      ngl::Vec3 v1(verts[f.m_vert[1]]);
      ngl::Vec3 v2(verts[f.m_vert[2]]);

      // transforming face data
      v0 = (ngl::Vec4(v0) * transform);
      v1 = (ngl::Vec4(v1) * transform);
      v2 = (ngl::Vec4(v2) * transform);

      // extracting normal data
      ngl::Vec3 n0(normals[f.m_norm[0]] * nTransform);
      ngl::Vec3 n1(normals[f.m_norm[1]] * nTransform);
      ngl::Vec3 n2(normals[f.m_norm[2]] * nTransform);

      Triangle t(v0,  v1,  v2,
                 n0,  n1,  n2,
                 uv0, uv1, uv2);
      meshOut->addTri(t);
    }
    auto prim = std::make_shared<GeometricPrim>(meshOut, m_currentMat);
    m_scene->addPrim(prim);
  }
}

void SceneParser::parseMat(const char *_begin)
{
  // setting default values
  ngl::Colour colour(0.4, 0.4, 0.4, 1);
  int smoothness = 0;
  double IOR = 1;
  bool isTransparent = false;
  bool isReflective = false;
  std::string texFile = "";

  // the first 3 real numbers are the base colour, then smoothness, ior, istransparent and is reflective
  // the file name is an optional strring on the end
  srule mat = "MAT:" >>
              spt::real_p[spt::assign_a(colour.m_r)] >>
              spt::real_p[spt::assign_a(colour.m_g)] >>
              spt::real_p[spt::assign_a(colour.m_b)] >>
              spt::int_p[spt::assign_a(smoothness)] >>
              spt::real_p[spt::assign_a(IOR)] >>
              spt::int_p[spt::assign_a(isTransparent)] >>
              spt::int_p[spt::assign_a(isReflective)] >>
              (*(+spt::alnum_p >> "/") >>
              +spt::alnum_p >> "." >> +spt::alnum_p)[spt::assign_a(texFile)];

  // parse file according to rule defined above
  spt::parse(_begin, mat, spt::space_p);

  // create material from extracted data
  m_currentMat = std::make_shared<Material>(colour, smoothness, IOR, isTransparent, isReflective, texFile);
}

void SceneParser::parseLight(const char *_begin)
{
  // default light values
  ngl::Colour colour(1, 1, 1);
  ngl::Vec3 pos(0, 0, 0);
  double intensity = 5;

  // first three values are position, then colour then intensity
  srule light = "LIGHT:" >>
                spt::real_p[spt::assign_a(pos[0])] >>
                spt::real_p[spt::assign_a(pos[1])] >>
                spt::real_p[spt::assign_a(pos[2])] >>
                spt::real_p[spt::assign_a(colour.m_r)] >>
                spt::real_p[spt::assign_a(colour.m_g)] >>
                spt::real_p[spt::assign_a(colour.m_b)] >>
                spt::real_p[spt::assign_a(intensity)];

  // parse line in using rule defined above
  spt::parse(_begin, light, spt::space_p);

  // adding a light to the scene using the extracted data
  m_scene->addLight(Light(pos, colour, intensity));
}

void SceneParser::parseTranslate(const char *_begin)
{
  ngl::Vec3 t(0, 0 , 0);

  // a translate requires 3 reals, tx, ty and tz
  srule translate = "TRANSLATE:" >>
                    spt::real_p[spt::assign_a(t[0])] >>
                    spt::real_p[spt::assign_a(t[1])] >>
                    spt::real_p[spt::assign_a(t[2])];

  // parse line with rule defined above
  spt::parse(_begin, translate, spt::space_p);

  // sets current transform using extracted data
  m_currentTransform.setPosition(t);
}

void SceneParser::parseRotate(const char *_begin)
{
  ngl::Vec3 r(0, 0 , 0);

  // rotate requires 3 reals, rx, ry and rz
  srule rotate = "ROTATE:" >>
                spt::real_p[spt::assign_a(r[0])] >>
                spt::real_p[spt::assign_a(r[1])] >>
                spt::real_p[spt::assign_a(r[2])];

  // pares the line using the rotate rule
  spt::parse(_begin, rotate, spt::space_p);

  // set the current rotation
  m_currentTransform.setRotation(r);
}

