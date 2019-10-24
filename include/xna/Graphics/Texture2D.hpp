/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <iostream>
#include <cstdio>
#include <string.h>

namespace xna::graphics {

    // Texture2D is able to store and configure a texture in OpenGL.
    // It also hosts utility functions for easy management.
    class Texture2D
    {
    public:

        Texture2D()
            : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilter_Min(GL_LINEAR), mFilter_Max(GL_LINEAR)
        {
            glGenTextures(1, &Id);
        }

        Texture2D(char* path)
            : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilter_Min(GL_LINEAR), mFilter_Max(GL_LINEAR)
        {
            mPath = strdup(path);
            glGenTextures(1, &Id);
        }

        Texture2D(char* path, bool alpha)
            : Width(0), Height(0), 
                Internal_Format(alpha ? GL_RGBA : GL_RGB), 
                Image_Format(alpha ? GL_RGBA : GL_RGB), 
                mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilter_Min(GL_LINEAR), mFilter_Max(GL_LINEAR)
        {
            mPath = strdup(path);
            glGenTextures(1, &Id);
        }

        void Generate(GLuint width, GLuint height, unsigned char* data)
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

        void Bind() const
        {
            glBindTexture(GL_TEXTURE_2D, Id);
        }    
        
    public:
        // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        GLuint Id;
        // Texture image dimensions
        GLuint Width, Height; // Width and height of loaded image in pixels
        // Texture Format
        GLuint Internal_Format; // Format of texture object
        GLuint Image_Format; // Format of loaded image
        // Texture configuration
    private:
        GLuint mWrap_S; // Wrapping mode on S axis
        GLuint mWrap_T; // Wrapping mode on T axis
        GLuint mFilter_Min; // Filtering mode if texture pixels < screen pixels
        GLuint mFilter_Max; // Filtering mode if texture pixels > screen pixels
        char* mPath;
        // Constructor (sets default texture modes)
    };
}