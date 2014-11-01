/*
 * file_loader.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Erik Ashcraft
 */

#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

#include "line_reader.h"
#include "texture.h"

class FileLoader {
    public:
        FileLoader();
        ~FileLoader();

        LineReader* loadFile(std::string filepath);
        SDL_Surface* loadBmp(std::string filepath);
        GLbyte *loadTGA(std::string filepath, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
        Texture* loadTexture(std::string filepath);
        Texture* loadParitcleTexture(std::string filepath);
        std::vector<std::vector<float> > loadHeightMap(std::string filepath);
        //GLuint loadShader(std::string filepath, GLuint mode);
        //GLuint loadVertexShader(std::string filepath);
        //GLuint loadFragmentShader(std::string filepath);
        //void load3ds(std::string filepath);
};

#endif
