#include "texturehelper.h"
#include <assert.h>

TextureHelper::TextureHelper() {
    qDebug("To call initializeOpenGLFunctions!");
    //好像必须在initializeGL调用！
    initializeOpenGLFunctions();
    qDebug("Call initializeOpenGLFunctions end!");
}

TextureHelper::~TextureHelper() {

}

GLuint TextureHelper::loadTexture(const char * resource, bool mipMap) {
    QImage image = QImage(resource).mirrored();
    assert(!image.isNull());

    return generateTexture(&image, mipMap, GL_RGBA, GL_UNSIGNED_BYTE);
}

GLuint TextureHelper::generateTexture(QImage * bitmap
                                      , bool mipMap
                                      , int internalFormat
                                      , int type) {
    if (mipMap) {
        return generateTexture(bitmap
                               , GL_LINEAR_MIPMAP_LINEAR
                               , GL_LINEAR
                               , internalFormat, type);
    } else {
        return generateTexture(bitmap
                               , GL_NEAREST
                               , GL_NEAREST
                               , internalFormat, type);
    }
}

GLuint TextureHelper::generateTexture(const char * mapData
                                      , int width
                                      , int height
                                      , bool mipMap
                                      , int internalFormat
                                      , int type) {
    qDebug("generateTexture entry! width: %d, height:%d"
           , width, height);

    GLuint minFilterType, maxFilterType;
    if (mipMap) {
        minFilterType = GL_LINEAR_MIPMAP_LINEAR;
        maxFilterType = GL_LINEAR;
    } else {
        minFilterType = GL_NEAREST;
        maxFilterType = GL_NEAREST;
    }
    return generateTexture(mapData
                           , width
                           , height
                           , minFilterType
                           , maxFilterType
                           , internalFormat
                           , type);

}

GLuint TextureHelper::generateTexture(QImage * bitmap
                                      , int minFilterType
                                      , int maxFilterType
                                      , int internalFormat
                                      , int type) {
    if (!bitmap) {
        qDebug("QImage is null!");
        return 0;
    }

    GLuint textureObjectId;
    glGenTextures(1, &textureObjectId);

    assert (textureObjectId != 0);

    bindTexture2DImage(textureObjectId
                       , bitmap
                       , minFilterType
                       , maxFilterType
                       , internalFormat
                       , type);
    qDebug("Generate a texture id: %d", textureObjectId);
    return textureObjectId;
}

GLuint TextureHelper::generateTexture(const char *mapData
                                      , int width
                                      , int height
                                      , int minFilterType
                                      , int maxFilterType
                                      , int internalFormat
                                      , int type) {
    assert (!mapData);

    GLuint textureObjectId;
    glGenTextures(1, &textureObjectId);
    assert (!textureObjectId);

    bindTexture2DImage(textureObjectId
                       , mapData
                       , width
                       , height
                       , minFilterType
                       , maxFilterType
                       , internalFormat
                       , type);
    qDebug("Generate a texture id: %d", textureObjectId);
    return textureObjectId;
}

void TextureHelper::bindTexture2DImage(GLuint textureObjectId
                                       , QImage * bitmap
                                       , bool mipMap
                                       , int internalFormat
                                       , int type) {
    if (mipMap) {
        bindTexture2DImage(textureObjectId
                           , bitmap
                           , GL_LINEAR_MIPMAP_LINEAR
                           , GL_LINEAR
                           , internalFormat, type);
    } else {
        bindTexture2DImage(textureObjectId
                           , bitmap
                           , GL_NEAREST
                           , GL_NEAREST
                           , -internalFormat, type);
    }
}

void TextureHelper::bindTexture2DImage(GLuint textureObjectId
                                       , const char * mapData
                                       , int width
                                       , int height
                                       , bool mipMap
                                       , int internalFormat
                                       , int type) {
    if (mipMap) {
        bindTexture2DImage(textureObjectId
                           , mapData
                           , width
                           , height
                           , GL_LINEAR_MIPMAP_LINEAR
                           , GL_LINEAR
                           , internalFormat
                           , type);
    } else {
        bindTexture2DImage(textureObjectId
                           , mapData
                           , width
                           , height
                           , GL_NEAREST
                           , GL_NEAREST
                           , -internalFormat
                           , type);
    }
}

void TextureHelper::bindTexture2DImage(GLuint textureObjectId
                                       , QImage * bitmap
                                       , int minFilterType
                                       , int maxFilterType
                                       , int internalFormat
                                       , int type) {
    glBindTexture(GL_TEXTURE_2D, textureObjectId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilterType);

    glTexImage2D(GL_TEXTURE_2D
                 , 0                    //level
                 , internalFormat       //internal format
                 , bitmap->width()      //width
                 , bitmap->height()     //height
                 , 0                    //border
                 , GL_RGBA              //format
                 , type                 //GL_UNSIGNED_BYTE... etc
                 , bitmap->bits());     //pixels

    if (minFilterType == GL_LINEAR_MIPMAP_LINEAR
            || minFilterType == GL_LINEAR_MIPMAP_NEAREST
            || minFilterType == GL_NEAREST_MIPMAP_LINEAR
            || minFilterType == GL_NEAREST_MIPMAP_NEAREST) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureHelper::bindTexture2DImage(GLuint textureObjectId
                                       , const char * mapData
                                       , int width
                                       , int height
                                       , int minFilterType
                                       , int maxFilterType
                                       , int internalFormat
                                       , int type) {
    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glBindTexture(GL_TEXTURE_2D, textureObjectId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilterType);

    // Load the texture
    glTexImage2D(GL_TEXTURE_2D
                 , 0
                 , internalFormat    //GL_LUMINANCE
                 , width
                 , height
                 , 0
                 , internalFormat    //GL_LUMINANCE
                 , type              //GL_UNSIGNED_BYTE
                 , mapData);

    if (minFilterType == GL_LINEAR_MIPMAP_LINEAR
            || minFilterType == GL_LINEAR_MIPMAP_NEAREST
            || minFilterType == GL_NEAREST_MIPMAP_LINEAR
            || minFilterType == GL_NEAREST_MIPMAP_NEAREST) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void TextureHelper::deleteTexture(GLuint texture) {
    if (texture == 0)
        return;

    glDeleteTextures(1, &texture);
}

GLuint TextureHelper::generateTexture(QImage * bitmap, bool mipMap) {
    return generateTexture(bitmap, mipMap, GL_RGBA, GL_UNSIGNED_BYTE);

}
