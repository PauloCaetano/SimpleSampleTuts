QT += core
QT -= gui

CONFIG += c++11
QMAKE_CXXFLAGS += -Wall


TARGET = SSHExec
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

####
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

LIBS += -lboost_system-mt
LIBS += -lmswsock -lsecur32 -lws2_32
LIBS += -lssh2

SOURCES += main.cpp \
    ssh/sshsession.cpp \
    ssh/sessionconnection.cpp \
    ssh/sshcommand.cpp \
    utils/asyncloop.cpp \
    ssh/remotesessionhandle.cpp \
    ssh/sessionauthenticator.cpp \
    ssh/sessionhandle.cpp \
    ssh/channelhandle.cpp \
    ssh/remotechannelhandle.cpp

HEADERS += \
    ssh/sshexception.h \
    utils/exception.h \
    base/exception.h \
    ssh/misc.h \
    ssh/sshsession.h \
    ssh/sessionconnection.h \
    ssh/sshcommand.h \
    utils/asyncloop.h \
    ssh/remotesessionhandle.h \
    ssh/sessionauthenticator.h \
    ssh/sessionhandle.h \
    utils/misc.h \
    ssh/channelhandle.h \
    ssh/remotechannelhandle.h
