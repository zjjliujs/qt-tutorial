#ifndef QGL_TUTORIAL05_H
#define QGL_TUTORIAL05_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QKeyEvent>

#include "texturehelper.h"

//#define USE_QT_TEXTURE_WRAP
//#define USE_QT_SHADER_PROGRAM

class QOpenGLTexture;

class Tutorial05 : public QOpenGLWidget, protected QOpenGLFunctions {
  public:
    Tutorial05( QWidget *parent = 0 );
    ~Tutorial05();

  protected:
    void initializeGL(void);
    void resizeGL( int w, int h );
    void paintGL();
    void keyPressEvent( QKeyEvent *e);
    void timerEvent(QTimerEvent*);

  private:
#ifdef USE_QT_SHADER_PROGRAM
    QOpenGLShaderProgram shaderProgram;
#endif
    GLuint programID;
    TextureHelper * textureHelper;
    QMatrix4x4 MVP;
#ifdef USE_QT_TEXTURE_WRAP
    QOpenGLTexture* mTexture;
#else
    GLuint textureId;
#endif
    GLuint matrixID;
    GLuint aPostion;
    GLuint aTextureCoord;
    GLuint TextureID;
    GLuint vertexbuffer;
    GLuint uvbuffer;
};


#endif // QGL_TUTORIAL05_H
