#include "qgl_tutorial03.h"
#include <iostream>

#include <QApplication>
#include <QOpenGLShaderProgram>
#include "shaderutils.h"

#define RES_SHADER_SOURCE

static int timer_interval = 100;        // timer interval (millisec)
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

static const GLfloat triangle_colors[] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
};

static const char * vertexShaderSrc = {
    "#version 320 es\n"
    "in vec3 vertexPosition_modelspace;\n"
    "uniform mat4 MVP;\n"
    "void main() {\n"
    "    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"
    "}\n"
};

static const char * fragShaderSrc = {
    "#version 320 es\n"
    "precision mediump float;"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4(1, 0, 0, 1);\n"
    "}\n"
};

Tutorial03::Tutorial03( QWidget *parent ) : QOpenGLWidget(parent) {
    startTimer( timer_interval );
    qDebug("%s", vertexShaderSrc);
    qDebug("%s", fragShaderSrc);
}

Tutorial03::~Tutorial03() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
}

void Tutorial03::initializeGL(void) {
    // initialize OpenGL
    initializeOpenGLFunctions();

#ifdef USE_QT_SHADER_PROGRAM
    bool success;
    // load and compile vertex shader
    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/res/simple_shader.vert");

    // load and compile fragment shader
    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/res/simple_shader.frag");

    // link the shader program
    shaderProgram.link();

    programID = shaderProgram.programId();
#else
#ifdef RES_SHADER_SOURCE
    ShaderUtils shaderUtils;
    programID = shaderUtils.esLoadProgramFile(":/res/simple_shader.vert", ":/res/simple_shader.frag");
#else
    programID = shaderUtils.esLoadProgramSource(vertexShaderSrc, fragShaderSrc);
#endif
#endif

    // Get a handle for our buffers
    vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");

    // Get a handle to the colors
    color_location = glGetAttribLocation(programID, "v_color");

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//  glGenBuffers(1, &colorbuffer);
//  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);

    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
}

void Tutorial03::paintGL(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

#ifdef USE_QT_SHADER_PROGRAM
    shaderProgram.bind();
#else
    glUseProgram(programID);
#endif
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, MVP.data());

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        vertexPosition_modelspaceID, // The attribute we want to configure
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    /*
      // 2nd attribute buffer : color
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
      glVertexAttribPointer(
        color_location, // The attribute we want to configure
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
      );
    */
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

#ifdef USE_QT_SHADER_PROGRAM
    shaderProgram.release();
#endif
}


void Tutorial03::timerEvent(QTimerEvent*) {
    static float rotval = 4.0;
    MVP.rotate(rotval, 1.0, 0.0, 0.0);
    update();
}

void Tutorial03::resizeGL(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    QMatrix4x4 projection;
    projection.perspective(45.0, ((float)w) / h, 0.1, 100.0);

    // Camera matrix
    QMatrix4x4 view;
    view.lookAt( //QVector3D(4, 3, 3), // Camera is at (4,3,3), in World Space
        QVector3D(1, 0, 3),
        QVector3D(0, 0, 0), // and looks at the origin
        QVector3D(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    QMatrix4x4 model;
    model.setToIdentity();

    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP =  projection * view * model; // Remember, matrix multiplication is the other way around
}

void Tutorial03::keyPressEvent(QKeyEvent *e) {
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

    Tutorial03 w;
    w.show();
    return a.exec();
}
