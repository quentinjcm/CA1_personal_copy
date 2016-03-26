TARGET=myRT

QT+=gui

CONFIG+=c++11
CONFIG+=-pthread
CONFIG-=app_bundle

OBJECTS_DIR=obj

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/Triangle.cpp \
         $$PWD/src/TriangleData.cpp \
         $$PWD/src/TriangleMesh.cpp \
         $$PWD/src/Ray.cpp \
         $$PWD/src/BBox.cpp \
         $$PWD/src/SceneParser.cpp \
         $$PWD/src/IsectData.cpp \
         $$PWD/src/Film.cpp \
         $$PWD/src/Camera.cpp \
         $$PWD/src/Primative.cpp \
         $$PWD/src/GeometricPrim.cpp \
         $$PWD/src/Meshes.cpp \
         $$PWD/src/Renderer.cpp \
         $$PWD/src/Material.cpp \
         $$PWD/src/SDLWindow.cpp \
         $$PWD/src/Scene.cpp \
         $$PWD/src/Light.cpp \
         $$PWD/src/TextureFile.cpp \
         $$PWD/src/RenderTask.cpp

HEADERS+=$$PWD/include/Triangle.hpp \
         $$PWD/include/TriangleData.hpp \
         $$PWD/include/TriangleMesh.hpp \
         $$PWD/include/Ray.hpp \
         $$PWD/include/BBox.hpp \
         $$PWD/include/SceneParser.hpp \
         $$PWD/include/IsectData.hpp \
         $$PWD/include/Film.hpp \
         $$PWD/include/Camera.hpp \
         $$PWD/include/Primative.hpp \
         $$PWD/include/GeometricPrim.hpp \
         $$PWD/include/Meshes.hpp \
         $$PWD/include/Renderer.hpp \
         $$PWD/include/Material.hpp \
         $$PWD/include/SDLWindow.hpp \
         $$PWD/include/Scene.hpp \
         $$PWD/include/Light.hpp \
         $$PWD/include/TextureFile.hpp \
         $$PWD/include/RenderTask.hpp

include($(HOME)/NGL/UseNGL.pri)

INCLUDEPATH+=./include

QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)


LIBS+=$$system(sdl2-config --libs)
LIBS+= -lboost_system




OTHER_FILES+=todo.txt \
             lighting.txt
