#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T20:36:25
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = Tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

# SEE http://www.qtcentre.org/threads/23655-Does-Qt-Creator-understand-debug-release-scopes-in-pro-files
# OR http://www.qtcentre.org/threads/30430-How-to-set-pro-file-about-debug-and-release
####
CONFIG(debug, debug|release) {
CONFIG -= debug release
CONFIG += debug
}

CONFIG(release, debug|release) {
CONFIG -= debug release
CONFIG += release
}
####

# You must define the path to your libs
LIB_HOME = "C:/Dev/lib2/mingw32_48"
BOOST_HOME = $${LIB_HOME}/boost/boost1540
ICU_HOME= $${LIB_HOME}/icu/icu512
POCO_HOME = $${LIB_HOME}/poco/poco146p2

debug {
!build_pass:message("Building DEBUG version")

BOOST_DEBUG = -d
POCO_DEBUG = d

BOOST_PATH = $${BOOST_HOME} # BOOST HAS BOTH DEBUG AND RELEASE LIBS IN THE SAME FOLDER
POCO_PATH = $${POCO_HOME} # POCO HAS BOTH DEBUG AND RELEASE LIBS IN THE SAME FOLDER
ICU_PATH = $${ICU_HOME}/debug
}

release {
!build_pass:message("Building RELEASE version")

BOOST_DEBUG =
POCO_DEBUG =

BOOST_PATH = $${BOOST_HOME} # BOOST HAS BOTH DEBUG AND RELEASE LIBS IN THE SAME FOLDER
POCO_PATH = $${POCO_HOME} # POCO HAS BOTH DEBUG AND RELEASE LIBS IN THE SAME FOLDER
ICU_PATH = $${ICU_HOME}/release
}

INCLUDEPATH += "$${BOOST_PATH}/include/boost-1_54"
INCLUDEPATH += "$${POCO_PATH}/include"

BOOST_COMPILER = mgw48
BOOST_VERSION = 1_54

LIBS += -L"$${BOOST_PATH}/lib" \
    -lboost_filesystem-$${BOOST_COMPILER}-mt$${BOOST_DEBUG}-$${BOOST_VERSION} \
    -lboost_system-$${BOOST_COMPILER}-mt$${BOOST_DEBUG}-$${BOOST_VERSION} \
    -lboost_log-$${BOOST_COMPILER}-mt$${BOOST_DEBUG}-$${BOOST_VERSION} \
    -lboost_thread-$${BOOST_COMPILER}-mt$${BOOST_DEBUG}-$${BOOST_VERSION} \
    -lboost_log_setup-$${BOOST_COMPILER}-mt$${BOOST_DEBUG}-$${BOOST_VERSION}

LIBS += -L"$${POCO_PATH}/lib" -lPocoFoundation$${POCO_DEBUG} -lPocoUtil$${POCO_DEBUG}

LIBS += -L"$${ICU_PATH}"/lib

SOURCES += preprocessor.cpp

HEADERS += macro_overload_base.h \
    ../src/preprocessor/log_interface_type.h \
    ../src/preprocessor/li_outop.h \
    ../src/preprocessor/boost_log.h \
    ../src/preprocessor/poco_log.h \
    ../src/preprocessor/li_concat.h

