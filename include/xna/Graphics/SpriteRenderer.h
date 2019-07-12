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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "GLShader.h"

namespace xna::graphics {

    class SpriteRenderer
    {
    public:
        // Constructor (inits shaders/shapes)
        SpriteRenderer(GLShader &shader);
        // Destructor
        ~SpriteRenderer();
        // Renders a defined quad textured with given sprite
        void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    private:
        // Render state
        GLShader Shader; 
        GLuint QuadVAO;
        // Initializes and configures the quad's buffer and vertex attributes
        void InitRenderData();
    };
}