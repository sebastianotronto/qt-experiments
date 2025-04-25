# Source files
SOURCES = main.cpp adapter.cpp nissywindow.cpp solvercfgwidget.cpp
HEADERS = adapter.h nissywindow.h solvercfgwidget.h
FORMS = nissywindow.ui solvercfgwidget.ui

# Add nissy backend headers and code
SOURCES += ../nissy-core/cpp/nissy.cpp
HEADERS += ../nissy-core/cpp/nissy.h

# Compiler configuration
CONFIG += qt debug c++20
LIBS += ../nissy-core/nissy.o
QT += widgets concurrent 

# Destination folders for generated files
MOC_DIR = generated_files
UI_DIR = generated_files
OBJECTS_DIR = build
