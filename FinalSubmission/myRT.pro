TARGET=myRT

CONFIG+=c++14
CONFIG+=-pthread

OBJECTS_DIR=obj

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/Triangle.cpp \
         $$PWD/src/TriangleMesh.cpp \
         $$PWD/src/Ray.cpp \
         $$PWD/src/BBox.cpp \
         $$PWD/src/Parser.cpp \
         $$PWD/src/IsectData.cpp \
         $$PWD/src/Film.cpp \
         $$PWD/src/Camera.cpp \
         $$PWD/src/Primative.cpp \
         $$PWD/src/GeometricPrim.cpp \
         $$PWD/src/Meshes.cpp \
         $$PWD/src/Renderer.cpp \
         $$PWD/src/Material.cpp \
         $$PWD/src/SDLWindow.cpp \
         $$PWD/src/RenderTask.cpp

HEADERS+=$$PWD/include/Triangle.hpp \
         $$PWD/include/TriangleMesh.hpp \
         $$PWD/include/Ray.hpp \
         $$PWD/include/BBox.hpp \
         $$PWD/include/Parser.hpp \
         $$PWD/include/IsectData.hpp \
         $$PWD/include/Film.hpp \
         $$PWD/include/Camera.hpp \
         $$PWD/include/Primative.hpp \
         $$PWD/include/GeometricPrim.hpp \
         $$PWD/include/Meshes.hpp \
         $$PWD/include/Renderer.hpp \
         $$PWD/include/Material.hpp \
         $$PWD/include/SDLWindow.hpp \
         $$PWD/include/RenderTask.hpp

include($(HOME)/NGL/UseNGL.pri)

INCLUDEPATH+=./include

QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)

LIBS+=$$system(sdl2-config --libs)

OTHER_FILES+=todo.txt
