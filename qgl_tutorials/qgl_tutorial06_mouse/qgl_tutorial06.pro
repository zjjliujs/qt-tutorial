#-------------------------------------------------
#
# Project created by QtCreator 2013-10-02T22:05:16
#
#-------------------------------------------------

QT       += core gui widgets opengl

TARGET = qgl_tutorial06
TEMPLATE = app

mac {
    CONFIG -= app_bundle
}

SOURCES +=\
        qgl_tutorial06.cpp \
        shaderutils.cpp

HEADERS  += qgl_tutorial06.h \
    shaderutils.h

RESOURCES += GLShaders.qrc

