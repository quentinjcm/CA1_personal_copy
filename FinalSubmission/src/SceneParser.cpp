//stdlib includes
#include <string>
#include <memory>
#include <fstream>

//boost includes
#include <boost/bind.hpp>
#include <boost/spirit/include/classic.hpp>

//ngl includes
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Mat4.h>
#include <ngl/Mat3.h>
#include <ngl/Colour.h>
#include <ngl/Obj.h>
#include <ngl/NGLStream.h>

//my includes
#include "SceneParser.hpp"
#include "Scene.hpp"
#include "ProceduralMeshes.hpp"
#include "GeometricPrim.hpp"
#include "Light.hpp"
#include "Triangle.hpp"

//taken from looking at ngl obj
namespace spt = boost::spirit::classic;
typedef spt::rule<spt::phrase_scanner_t> srule;

SceneParser::SceneParser(std::string _fileName, std::shared_ptr<Scene> _scene):
  m_scene(_scene),
  m_fileName(_fileName)
{
  //building a default material
  m_currentMat = std::make_shared<Material>(ngl::Colour(.3, .3, .3), 10, 1.5, 0, 1, "textures/uvGrid.png");
}

void SceneParser::parseSphere(const char *_begin)
{
  double radius = 0;
  int divisions = 4;

  srule sphere = "SPHERE:" >>
                 spt::int_p[spt::assign_a(divisions)] >>
                 spt::real_p[spt::assign_a(radius)];

  spt::parse(_begin, sphere, spt::space_p);
  std::cout << "creating prim " << radius << ", " << divisions << std::endl;
  auto prim = std::make_shared<GeometricPrim>(ProceduralMeshes::pSphere(radius, divisions, m_currentTransform), m_currentMat);
  m_scene->addPrim(prim);
}

void SceneParser::parsePlane(const char *_begin)
{
  double width = 1;
  double height = 1;

  srule plane = "PLANE:" >>
                spt::real_p[spt::assign_a(width)] >>
                spt::real_p[spt::assign_a(height)];

  spt::parse(_begin, plane, spt::space_p);
  auto prim = std::make_shared<GeometricPrim>(ProceduralMeshes::pPlane(width, height, m_currentTransform), m_currentMat);
  m_scene->addPrim(prim);
}

void SceneParser::parseObj(const char *_begin)
{
  std::string fileName;

  srule obj = "OBJ:" >>
               (*(+spt::alnum_p >> "/") >>
               +spt::alnum_p >> ".obj")[spt::assign_a(fileName)];

  spt::parse(_begin, obj, spt::space_p);
  std::cout << "opening obj " << fileName.c_str() << std::endl;
  ngl::Obj objMesh;
  objMesh.load(fileName, false);
  std::cout << "opened obj" << std::endl;
  if (objMesh.isTriangular()){
    ngl::Mat4 transform(m_currentTransform.getMatrix());
    ngl::Mat3 nTransform(transform);
    //nt.transpose();
    nTransform.inverse();

    auto meshOut = std::make_shared<TriangleMesh>();
    std::vector<ngl::Vec3> verts = objMesh.getVertexList();
    std::vector<ngl::Vec3> normals = objMesh.getNormalList();
    std::vector<ngl::Vec3> uvs = objMesh.getTextureCordList();
    std::vector<ngl::Face> faces = objMesh.getFaceList();
    for (ngl::Face f: faces){
      if (true){
        //converting uv cords from vec3 to vec2
        ngl::Vec2 uv0(uvs[f.m_tex[0]][0], uvs[f.m_tex[0]][1]);
        ngl::Vec2 uv1(uvs[f.m_tex[1]][0], uvs[f.m_tex[1]][1]);
        ngl::Vec2 uv2(uvs[f.m_tex[2]][0], uvs[f.m_tex[2]][1]);
        ngl::Vec3 v0 = verts[f.m_vert[0]];
        ngl::Vec3 v1 = verts[f.m_vert[1]];
        ngl::Vec3 v2 = verts[f.m_vert[2]];

        v0 = (ngl::Vec4(v0) * transform);
        v1 = (ngl::Vec4(v1) * transform);
        v2 = (ngl::Vec4(v2) * transform);
        Triangle t(v0, v1, v2,
                   normals[f.m_norm[0]] * nTransform,
                   normals[f.m_norm[1]] * nTransform,
                   normals[f.m_norm[2]] * nTransform,
                   uv0,
                   uv1,
                   uv2);
        meshOut->addTri(t);
      }
    }
    auto prim = std::make_shared<GeometricPrim>(meshOut, m_currentMat);
    m_scene->addPrim(prim);
  }

}

void SceneParser::parseMat(const char *_begin)
{
  ngl::Colour colour(0, 0, 0, 1);
  int smoothness = 0;
  //double reflectivity = 0;
  double IOR = 1;
  bool isTransparent = false;
  bool isReflective = false;
  std::string texFile = "";
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


  spt::parse(_begin, mat, spt::space_p);
  std::cout << isTransparent << std::endl;
  m_currentMat = std::make_shared<Material>(colour, smoothness, IOR, isTransparent, isReflective, texFile);
}

void SceneParser::parseLight(const char *_begin)
{
  ngl::Colour colour(0, 0, 0);
  ngl::Vec3 pos(0, 0, 0);
  double intensity;

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

void SceneParser::parseTranslate(const char *_begin)
{
  ngl::Vec3 t(0, 0 , 0);

  srule translate = "TRANSLATE:" >>
                    spt::real_p[spt::assign_a(t[0])] >>
                    spt::real_p[spt::assign_a(t[1])] >>
                    spt::real_p[spt::assign_a(t[2])];

  spt::parse(_begin, translate, spt::space_p);
  m_currentTransform.setPosition(t);
}

void SceneParser::parseRotate(const char *_begin)
{
  ngl::Vec3 r(0, 0 , 0);

  srule rotate = "ROTATE:" >>
                spt::real_p[spt::assign_a(r[0])] >>
                spt::real_p[spt::assign_a(r[1])] >>
                spt::real_p[spt::assign_a(r[2])];

  spt::parse(_begin, rotate, spt::space_p);
  m_currentTransform.setRotation(r);
}

void SceneParser::parseScale(const char *_begin)
{
  ngl::Vec3 s(0, 0 , 0);

  srule scale = "SCALE:" >>
                spt::real_p[spt::assign_a(s[0])] >>
                spt::real_p[spt::assign_a(s[1])] >>
                spt::real_p[spt::assign_a(s[2])];

  spt::parse(_begin, scale, spt::space_p);
  m_currentTransform.setScale(s);
}

void SceneParser::parseScene()
{
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
  srule scale = ("SCALE:" >> *(spt::anychar_p))
                [bind(&SceneParser::parseScale, boost::ref(*this), _1)];
  srule rotate = ("ROTATE:" >> *(spt::anychar_p))
                [bind(&SceneParser::parseRotate, boost::ref(*this), _1)];

  std::ifstream fileIn(m_fileName.c_str());
  if (fileIn.is_open()){
    std::string line;
    while (std::getline(fileIn, line)){
      spt::parse(line.c_str(), comment | sphere | plane | obj | mat | light | scale | rotate | translate, spt::space_p);
    }
  }
}
