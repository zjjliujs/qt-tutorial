#ifndef TEXTUREHELPER_H
#define TEXTUREHELPER_H

#include <QOpenGLFunctions>
#include <QImage>

class TextureHelper: protected QOpenGLFunctions {
  public:
    TextureHelper();
    virtual ~TextureHelper();

  public:
    GLuint loadTexture(const char * resource, bool mipMap);

    GLuint generateTexture(QImage * img, bool mipMap) ;

    void deleteTexture(GLuint texture) ;

    GLuint generateTexture(QImage * img
                           , bool mipMap
                           , int internalFormat
                           , int type) ;

    GLuint generateTexture(const char * mapData
                           , int width
                           , int height
                           , bool mipMap
                           , int internalFormat
                           , int type) ;

    GLuint generateTexture(QImage * img
                           , int minFilterType
                           , int maxFilterType
                           , int internalFormat
                           , int type) ;

    GLuint generateTexture(const char * mapData
                           , int width
                           , int height
                           , int minFilterType
                           , int maxFilterType
                           , int internalFormat
                           , int type) ;

    void bindTexture2DImage(GLuint textureObjectId
                            , QImage * img
                            , bool mipMap
                            , int internalFormat
                            , int type) ;

    void bindTexture2DImage(GLuint textureObjectId
                            , const char * mapData
                            , int width
                            , int height
                            , bool mipMap
                            , int internalFormat
                            , int type) ;

    void bindTexture2DImage(GLuint textureObjectId
                            , QImage * img
                            , int minFilterType
                            , int maxFilterType
                            , int internalFormat
                            , int type) ;

    void bindTexture2DImage(GLuint textureObjectId
                            , const char * mapData
                            , int width
                            , int height
                            , int minFilterType
                            , int maxFilterType
                            , int internalFormat
                            , int type) ;
};

#endif // TEXTUREHELPER_H
