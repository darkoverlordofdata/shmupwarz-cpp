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
#include "Shader.h"

namespace xna::graphics {

    class SpriteRenderer
    {
    public:
        // // Constructor (inits shaders/shapes)
        // SpriteRenderer(Shader &shader);
        // // Destructor
        // ~SpriteRenderer();
        // // Renders a defined quad textured with given sprite
        // void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

        SpriteRenderer(Shader &shader)
        {
            mShader = shader;
            InitRenderData();
        }

        ~SpriteRenderer()
        {
            glDeleteVertexArrays(1, &mQuadVAO);
        }

        void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
        {
            // printf("%s (%d,%d)\n", texture.Path, texture.Width, texture.Height);
            // Prepare transformations
            mShader.Use();
            glm::mat4 model= {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
            model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

            model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
            model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
            model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

            model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

            mShader.SetMatrix4("model", model);

            // Render textured quad
            mShader.SetVector3f("spriteColor", color);

            glActiveTexture(GL_TEXTURE0);
            texture.Bind();

            glBindVertexArray(mQuadVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
        
    private:
        void InitRenderData()
        {
            // Configure VAO/VBO
            GLuint VBO;
            GLfloat vertices[] = { 
                // Pos      // Tex
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 

                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f
            };

            glGenVertexArrays(1, &mQuadVAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindVertexArray(mQuadVAO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }          
        // Render state
        Shader mShader; 
        GLuint mQuadVAO;
        // Initializes and configures the quad's buffer and vertex attributes
        // void InitRenderData();
    };
}