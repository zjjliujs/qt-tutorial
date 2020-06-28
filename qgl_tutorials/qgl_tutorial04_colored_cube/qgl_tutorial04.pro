#-------------------------------------------------
#
# Project created by QtCreator 2013-10-02T21:21:25
#
#-------------------------------------------------

QT       += core gui opengl widgets


TARGET = qgl_tutorial04
TEMPLATE = app

mac {
    CONFIG -= app_bundle
}

SOURCES +=\
        qgl_tutorial04.cpp \
        shaderutils.cpp

HEADERS  += qgl_tutorial04.h \
    shaderutils.h

RESOURCES += \
    GLShaders.qrc

