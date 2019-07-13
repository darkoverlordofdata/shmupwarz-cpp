/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "xna/Content/ResourceManager.h"

namespace xna {

    // Instantiate static variables
    std::map<std::string, Texture2D>    ResourceManager::Textures;
    std::map<std::string, Shader>       ResourceManager::Shaders;


    Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
    {
        Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
        return Shaders[name];
    }

    Shader& ResourceManager::GetShader(std::string name)
    {
        return Shaders[name];
    }

    Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
    {
        Textures[name] = LoadTextureFromFile(file, alpha);
        return Textures[name];
    }

    Texture2D& ResourceManager::GetTexture(std::string name)
    {
        return Textures[name];
    }

    void ResourceManager::Clear()
    {
        // (Properly) delete all shaders	
        for (auto iter : Shaders)
            glDeleteProgram(iter.second.Id);
        // (Properly) delete all textures
        for (auto iter : Textures)
            glDeleteTextures(1, &iter.second.Id);
    }

    Shader ResourceManager::LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
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

    Texture2D ResourceManager::LoadTextureFromFile(const GLchar *file, GLboolean alpha)
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
}