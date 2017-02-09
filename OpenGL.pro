# this is the name of the EXE
TARGET=OpenGL
# this adds a source file
SOURCES+=$$PWD/src/main.cpp
# add SDL include path
QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)
LIBS+=$$system(sdl2-config --libs)
LIBS+= -lGLU
OTHER_FILES+=.gitignore
