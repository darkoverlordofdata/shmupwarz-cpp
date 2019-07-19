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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../Graphics/Texture2D.hpp"
#include "../Graphics/Shader.hpp"
namespace xna {

    using namespace graphics;
    // A static singleton ResourceManager class that hosts several
    // functions to load Textures and Shaders. Each loaded texture
    // and/or shader is also stored for future reference by string
    // handles. All functions and resources are static and no 
    // public constructor is defined.
    class ResourceManager
    {
    public:
        // Resource storage
        static inline std::map<std::string, Shader>    Shaders = std::map<std::string, Shader>();
        static inline std::map<std::string, Texture2D> Textures = std::map<std::string, Texture2D>();

        // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
        static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
        {
            ResourceManager::Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
            return ResourceManager::Shaders[name];
        }

        // Retrieves a stored sader
        static Shader& GetShader(std::string name)
        {
            return ResourceManager::Shaders[name];
        }

        // Loads (and generates) a texture from file
        static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
        {
            ResourceManager::Textures[name] = LoadTextureFromFile(file, alpha);
            return ResourceManager::Textures[name];
        }

        // Retrieves a stored texture
        static Texture2D& GetTexture(std::string name)
        {
            return ResourceManager::Textures[name];
        }

        // Properly de-allocates all loaded resources
        static void Clear()
        {
            // (Properly) delete all shaders	
            for (auto iter : Shaders)
                glDeleteProgram(iter.second.Id);
            // (Properly) delete all textures
            for (auto iter : Textures)
                glDeleteTextures(1, &iter.second.Id);
        }

    private:

        ResourceManager() { }

        static Shader LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
        {
            printf("vertex %s\n", vShaderFile);
            printf("fragment %s\n", fShaderFile);
            // 1. Retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;
            std::string geometryCode;
            try
            {
                // Open files
                std::ifstream vertexShaderFile(vShaderFile);
                std::ifstream fragmentShaderFile(fShaderFile);
                std::stringstream vShaderStream, fShaderStream;
                // Read file's buffer contents into streams
                vShaderStream << vertexShaderFile.rdbuf();
                fShaderStream << fragmentShaderFile.rdbuf();
                // close file handlers
                vertexShaderFile.close();
                fragmentShaderFile.close();
                // Convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
                // If geometry shader path is present, also load a geometry shader
                if (gShaderFile != nullptr)
                {
                    std::ifstream geometryShaderFile(gShaderFile);
                    std::stringstream gShaderStream;
                    gShaderStream << geometryShaderFile.rdbuf();
                    geometryShaderFile.close();
                    geometryCode = gShaderStream.str();
                }
            }
            catch (std::exception e)
            {
                std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
            }
            const GLchar *vShaderCode = vertexCode.c_str();
            const GLchar *fShaderCode = fragmentCode.c_str();
            const GLchar *gShaderCode = geometryCode.c_str();
            // 2. Now create shader object from source code
            Shader shader;
            shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
            return shader;
        }

        static Texture2D LoadTextureFromFile(const GLchar *file, GLboolean alpha)
        {
            // Create Texture object
            Texture2D texture((char*)file);
            if (alpha)
            {
                texture.Internal_Format = GL_RGBA;
                texture.Image_Format = GL_RGBA;
            }
            // Load image
            int width, height;
            
            SDL_Surface * surface = IMG_Load(file);
            if (SDL_MUSTLOCK(surface)) 
                SDL_LockSurface(surface);
            // Now generate texture
            printf("%s: (%d,%d)\n", file, surface->w, surface->h);
            texture.Generate(surface->w, surface->h, (unsigned char*)surface->pixels);
            if (SDL_MUSTLOCK(surface)) 
                SDL_UnlockSurface(surface);
            // And finally free image data
            SDL_FreeSurface(surface);
            return texture;
        }        
    // private:
    //     // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    //     ResourceManager() { }
    //     // Loads and generates a shader from file
    //     static Shader    LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    //     // Loads a single texture from file
    //     static Texture2D LoadTextureFromFile(const GLchar *file, GLboolean alpha);
    };
}