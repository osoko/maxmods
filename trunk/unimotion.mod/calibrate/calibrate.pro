TARGET=Calibrate
LIBS+=-L../Frameworks -lUniMotion
INCLUDEPATH+=../unimotion
FORMS=calibrate.ui
SOURCES=main.cpp
UI_DIR=build
MOC_DIR=build
OBJECTS_DIR=build
instlib.files=../Frameworks/libUniMotion.dylib
instlib.path=$${TARGET}.app/Contents/Frameworks
INSTALLS+=instlib
