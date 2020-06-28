#include "qgl_tutorial02.h"
#include <QApplication>
#include <QKeyEvent>
#include <QFileInfo>
#include <QOpenGLExtraFunctions>

#include "shaderutils.h"

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };


Tutorial02::Tutorial02( QWidget *parent ) : QOpenGLWidget(parent) {
    vertexID = 0;
}

Tutorial02::~Tutorial02() {
    glDeleteBuffers(1, &vertexbuffer);
}

void Tutorial02::initializeGL(void) {
    // initialize OpenGL
    initializeOpenGLFunctions();
#ifdef USE_QT_SHADER_PROGRAM
    shaderProgram = new QOpenGLShaderProgram;
#ifdef GLSL2_0
    success = shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":res/triangle.vsh");
    // load and compile fragment shader
    success = shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":res/triangle.fsh");
#else
    success = shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":res/triangle.vert");
    // load and compile fragment shader
    success = shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":res/triangle.frag");
#endif
    bool success;
    shaderProgram->link();
    programID = shaderProgram->programId();
#else
    ShaderUtils shaderUtils;
#ifdef GLSL2_0
    programID = shaderUtils.esLoadProgramFile(":res/triangle.vsh", ":res/triangle.fsh");
#else
    programID = shaderUtils.esLoadProgramFile(":res/triangle.vert", ":res/triangle.frag");
#endif

#endif

    // load and compile vertex shader

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    qDebug("Tutorial02::initializeGL, program ID: %d", programID);

    vertexID = glGetAttribLocation(programID, "vertex");
    qDebug("Tutorial02::initializeGL, vertex ID: %d", vertexID);

    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
}

void Tutorial02::paintGL(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    glUseProgram(programID);

    // Use our shader
    f->glUseProgram(programID);

    // 1rst attribute buffer : vertices
    f->glEnableVertexAttribArray(vertexID);
    f->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    f->glVertexAttribPointer(
        vertexID,           // The attribute we want to configure
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !
    f->glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    f->glDisableVertexAttribArray(0);
}

void Tutorial02::resizeGL(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void Tutorial02::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Escape:  /*  Escape Key */
        exit(0);
        break;
    default:
        break;
    }
    e->accept();  // Don't pass any key events to parent
}

/*  Main Loop
*  Open window with initial window size, title bar,
*  and handle input events.
*/
int main( int argc, char **argv ) {
    QApplication a( argc, argv );

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);

#ifdef CORE_CONTEXT_VERSION_SET
    // Request OpenGL 3.3 core or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.0 context");
        fmt.setVersion(3, 0);
    }
    QSurfaceFormat::setDefaultFormat(fmt);
#endif

    Tutorial02 w;
    w.show();
    return a.exec();
}

