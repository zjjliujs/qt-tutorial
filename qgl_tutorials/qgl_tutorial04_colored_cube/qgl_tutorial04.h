#ifndef QGL_TUTORIAL04_H
#define QGL_TUTORIAL04_H

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

//#define USE_QT_SHADER_PROGRAM

class Tutorial04 : public QOpenGLWidget, protected QOpenGLFunctions {
  public:
    Tutorial04( QWidget *parent = 0 );
    ~Tutorial04();

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
    GLuint MatrixID;
    GLuint psitionAttr;
    GLuint vertexbuffer;
    GLuint vertexColorID;
    GLuint color_location;
    GLuint colorbuffer;
    QMatrix4x4 MVP;
};

#endif // QGL_TUTORIAL04_H
