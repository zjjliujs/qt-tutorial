#-------------------------------------------------
#
# Project created by QtCreator 2013-10-02T22:05:16
#
#-------------------------------------------------

QT       += core gui widgets opengl

TARGET = qgl_tutorial05
TEMPLATE = app

mac {
    CONFIG -= app_bundle
}

SOURCES +=\
        qgl_tutorial05.cpp \
        shaderutils.cpp \
        texturehelper.cpp

HEADERS  += qgl_tutorial05.h \
    shaderutils.h \
    texturehelper.h

FORMS +=

RESOURCES += \
    GLShaders.qrc
