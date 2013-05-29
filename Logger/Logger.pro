#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T14:09:53
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Logger
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -v -U__STRICT_ANSI__ #-fdump-tree-all -Winline -save-temps

QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_LFLAGS_RELEASE =

# UNLESS YOU DEFINE THIS, YOU WON'T GET ANY LOGGING WITH POCO'S DEBUG/TRACE MACROS
# HOWEVER, IN MSVC THIS WILL CAUSE AN ERROR IN RELEASE BUILDS
DEFINES += _DEBUG

DEFINES += WANT_LOGGING=1

LIB_HOME = "C:/Dev/lib2/mingw32"

POCO_HOME = $${LIB_HOME}/poco/poco146

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

debug {
!build_pass:message("Building DEBUG version")

POCO_DEBUG = d

POCO_PATH = $${POCO_HOME} # POCO HAS BOTH DEBUG AND RELEASE LIBS IN THE SAME FOLDER
}

release {
!build_pass:message("Building RELEASE version")

POCO_DEBUG =

POCO_PATH = $${POCO_HOME} # POCO HAS BOTH DEBUG AND RELEASE LIBS IN THE SAME FOLDER
}

INCLUDEPATH += "$${POCO_PATH}/include"

BOOST_COMPILER = mgw47
BOOST_VERSION = 1_53

LIBS += -L"$${POCO_PATH}/lib" -lPocoFoundation$${POCO_DEBUG} -lPocoUtil$${POCO_DEBUG}


SOURCES += main.cpp \
    libclassmain.cpp \
    libclassutility1.cpp \
    libclassutility2.cpp \
    libclasssupport.cpp \
    logger.cpp

HEADERS += \
    libclassmain.h \
    libclassutility1.h \
    libclassutility2.h \
    libclasssupport.h \
    logger.h \
    lib_logger.h \
    loggercout.h \
    loggerbridge.h \
    checklibinterface.h
