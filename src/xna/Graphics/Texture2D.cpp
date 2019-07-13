/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "xna/Graphics/Texture2D.h"
namespace xna::graphics {

    Texture2D::Texture2D()
        : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilter_Min(GL_LINEAR), mFilter_Max(GL_LINEAR)
    {
        glGenTextures(1, &Id);
    }

    Texture2D::Texture2D(char* path)
        : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilter_Min(GL_LINEAR), mFilter_Max(GL_LINEAR)
    {
        mPath = strdup(path);
        glGenTextures(1, &Id);
    }

    void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data)
    {
        Width = width;
        Height = height;
        // Create Texture
        glBindTexture(GL_TEXTURE_2D, Id);
        glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
        // Set Texture wrap and filter modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrap_S);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrap_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilter_Min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilter_Max);
        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, Id);
    }
}