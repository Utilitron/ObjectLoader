/*
 * texture.h
 *
 *  Created on: Mar 23, 2014
 *      Author: Erik Ashcraft
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture {
    public:
        GLuint num;	//the id for the texture
        GLint width, height;

        Texture(GLuint tnum, GLint iWidth, GLint iHeight) {
            num = tnum;
            width = iWidth;
            height = iHeight;
        }
        ~Texture();
};

#endif
