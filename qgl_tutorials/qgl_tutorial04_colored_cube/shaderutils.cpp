#include "shaderutils.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

ShaderUtils::ShaderUtils() {
    initializeOpenGLFunctions();
}

ShaderUtils::~ShaderUtils() {

}

char * ShaderUtils::readRes(const char *res) {
    QFile file(res);
    bool f = file.open(QFile::ReadOnly | QFile::Text);
    if (!f) {
        qFatal("ShaderUtils::readRes! could not open file: %s", res);
        return 0;
    }
    QByteArray buffer = file.readAll();
    char * r = new char[buffer.size() + 1];
    strcpy(r, buffer.data());
    file.close();
    return r;
}


GLuint ShaderUtils::esLoadShader ( GLenum type, const char * shaderString) {
    GLuint shader;
    GLint compiled;

    //const char * shaderSrc = shaderString.toLatin1().data();
    qDebug ( "ShaderUtils::esLoadShader shader src:\n%s", shaderString);
    // Create the shader object
    shader = glCreateShader ( type );

    if ( shader == 0 ) {
        return 0;
    }

    // Load the shader source
    glShaderSource ( shader, 1, &shaderString, NULL );

    // Compile the shader
    glCompileShader ( shader );

    // Check the compile status
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

    if ( !compiled ) {
        int infoLen = 0;

        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

        if (infoLen > 1) {
            char infoLog[infoLen];
            glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
            qDebug ( "Error compiling shader:\n%s", infoLog );
        }

        glDeleteShader ( shader );
        return 0;
    }
    return shader;
}

GLuint ShaderUtils::esLoadProgramFile ( const char *vertShaderFile, const char *fragShaderFile ) {
    char *  vertexShader = readRes(vertShaderFile);
    //qDebug("vertexShader,\n%s\n", vertexShader);

    char *  fragShader = readRes(fragShaderFile);
    //qDebug("fragShader,\n%s\n", fragShader);

    GLuint r = esLoadProgramSource(vertexShader, fragShader);

    delete [] vertexShader;
    delete [] fragShader;
    return r;
}

//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint ShaderUtils::esLoadProgramSource ( const char * vertShaderSrc, const char * fragShaderSrc) {
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = esLoadShader ( GL_VERTEX_SHADER, vertShaderSrc );

    if ( vertexShader == 0 ) {
        return 0;
    }

    fragmentShader = esLoadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );

    if ( fragmentShader == 0 ) {
        glDeleteShader ( vertexShader );
        return 0;
    }

    // Create the program object
    programObject = glCreateProgram ( );

    if ( programObject == 0 ) {
        return 0;
    }

    glAttachShader ( programObject, vertexShader );
    glAttachShader ( programObject, fragmentShader );

    // Link the program
    glLinkProgram ( programObject );

    // Check the link status
    glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

    if ( !linked ) {
        GLint infoLen = 0;

        glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 ) {
            char infoLog[infoLen];
            glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
            qDebug ( "Error linking program:\n%s", infoLog );
        }

        glDeleteProgram ( programObject );
        return 0;
    }

    // Free up no longer needed shader resources
    glDeleteShader ( vertexShader );
    glDeleteShader ( fragmentShader );

    return programObject;
}
