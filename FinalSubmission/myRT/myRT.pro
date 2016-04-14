TARGET=myRT

QT+=gui \
    core \
    declarative

CONFIG+=c++11
CONFIG+= -v
CONFIG+=-pthread
CONFIG+=console
CONFIG-=app_bundle

OBJECTS_DIR=obj/

UI_HEADERS_DIR+= ui


isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/Triangle.cpp \
         $$PWD/src/TriangleMesh.cpp \
         $$PWD/src/Ray.cpp \
         $$PWD/src/BBox.cpp \
         $$PWD/src/SceneParser.cpp \
         $$PWD/src/Film.cpp \
         $$PWD/src/Camera.cpp \
         $$PWD/src/Primative.cpp \
         $$PWD/src/GeometricPrim.cpp \
         $$PWD/src/ProceduralMeshes.cpp \
         $$PWD/src/Renderer.cpp \
         $$PWD/src/Material.cpp \
         $$PWD/src/SDLWindow.cpp \
         $$PWD/src/Scene.cpp \
         $$PWD/src/TextureFile.cpp \
         $$PWD/src/RenderTask.cpp \
         $$PWD/src/Viewport.cpp

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
         $$PWD/include/ProceduralMeshes.hpp \
         $$PWD/include/Renderer.hpp \
         $$PWD/include/Material.hpp \
         $$PWD/include/SDLWindow.hpp \
         $$PWD/include/Scene.hpp \
         $$PWD/include/TextureFile.hpp \
         $$PWD/include/RenderTask.hpp \
         $$PWD/include/RenderSettings.hpp \
         $$PWD/include/Viewport.hpp


include($(HOME)/NGL/UseNGL.pri)

INCLUDEPATH+=./include

QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)

LIBS+=$$system(sdl2-config --libs)
LIBS+= -lboost_system

OTHER_FILES+=todo.txt \
             lighting.txt\
             scenes/* \
             textures/* \
             saves/*

FORMS += ui/viewport.ui
MOC_DIR += moc/
