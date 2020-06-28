#ifndef SHADERUTILS_H
#define SHADERUTILS_H

#include <QOpenGLFunctions>

class ShaderUtils: protected QOpenGLFunctions {
  public:
    ShaderUtils();
    virtual ~ShaderUtils();

  public:
    GLuint esLoadShader ( GLenum type, const char * shaderSrc ) ;
    GLuint esLoadProgramSource ( const char * vertShaderSrc, const char * fragShaderSrc );
    GLuint esLoadProgramFile ( const char *vertShaderFile, const char *fragShaderFile );

  private:
    char * readRes(const char * res);
};

#endif // SHADERUTILS_H
