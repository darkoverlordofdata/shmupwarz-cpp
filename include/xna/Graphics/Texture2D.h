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
        Texture2D();
        Texture2D(char* path);
        // Generates texture from image data
        void Generate(GLuint width, GLuint height, unsigned char* data);
        // Binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
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