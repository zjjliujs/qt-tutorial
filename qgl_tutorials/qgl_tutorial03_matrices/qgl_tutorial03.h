#ifndef QGL_TUTORIAL03_H
#define QGL_TUTORIAL03_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix>
#include <QKeyEvent>

//#define USE_QT_SHADER_PROGRAM

class Tutorial03 : public QOpenGLWidget, protected QOpenGLFunctions {
  public:
    Tutorial03( QWidget *parent = 0 );
    virtual ~Tutorial03();

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
    GLuint vertexPosition_modelspaceID;
    GLuint vertexbuffer;
    GLuint color_location;
    GLuint colorbuffer;
    QMatrix4x4 MVP;
};


#endif // QGL_TUTORIAL03_H
