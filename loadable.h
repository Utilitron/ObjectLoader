/*
 * loadable.h
 *
 *  Created on: Feb 15, 2014
 *      Author: Erik Ashcraft
 */

#ifndef LOADABLE_H
#define LOADABLE_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "glm/glm.hpp"

#include <stdio.h>
#include <vector>

#include "drawable.h"
#include "face.h"
#include "material.h"

class Loadable {
    public:
        Loadable() {
        }
        ~Loadable() {
        }

        std::vector<glm::vec2*> coordinates;
        std::vector<glm::vec3*> vertices;
        std::vector<Face*> faces;
        std::vector<glm::vec3*> normals;
        std::vector<Material*> materials;

        /**
         * drawObject()
         * called to draw the object
         **/
        void drawObject(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, bool texture) {
            glPushMatrix();
            std::string lastmat = "";
            glTranslatef(xPos, yPos, zPos);

            //if (this->getXrot() != 0.0)
            //	glRotatef(this->getXrot(),1.0,0.0,0.0);

            if (yRot != 0.0) glRotatef(yRot, 0.0, 1.0, 0.0);

            //if (this->getZrot() != 0.0)
            //	glRotatef(this->getZrot(),0.0,0.0,1.0);

            glTranslatef(-xPos, -yPos, -zPos);

            for (int i = 0; i < (int) faces.size(); i++) {
                if (faces[i]->material.compare(lastmat) != 0) {
                    lastmat = faces[i]->material;
                    Material* mat;
                    for (int i = 0; i < materials.size(); i++) {
                        if (lastmat.compare(materials[i]->name)) mat = materials[i];
                    }

                    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
                    glMaterialf(GL_FRONT, GL_SHININESS, mat->specular_coefficient);

                    if (texture && mat->hasTexture) {
                        glBindTexture(GL_TEXTURE_2D, mat->texture->num);
                    }
                }

                if (faces[i]->vertices.size() == 4) {

                    glBegin(GL_TRIANGLES);
                    if (0 < (int) faces[i]->normals.size()) {
                        glNormal3f(normals[faces[i]->normals[2] - 1]->x, normals[faces[i]->normals[2] - 1]->y, normals[faces[i]->normals[2] - 1]->z);
                        glNormal3f(normals[faces[i]->normals[3] - 1]->x, normals[faces[i]->normals[3] - 1]->y, normals[faces[i]->normals[3] - 1]->z);
                        glNormal3f(normals[faces[i]->normals[0] - 1]->x, normals[faces[i]->normals[0] - 1]->y, normals[faces[i]->normals[0] - 1]->z);
                    }

                    if (texture) glTexCoord2f(coordinates[faces[i]->coordinates[2] - 1]->x, coordinates[faces[i]->coordinates[2] - 1]->y);
                    glVertex3f(xPos + vertices[faces[i]->vertices[2] - 1]->x, yPos + vertices[faces[i]->vertices[2] - 1]->y, zPos + vertices[faces[i]->vertices[2] - 1]->z);
                    if (texture) glTexCoord2f(coordinates[faces[i]->coordinates[3] - 1]->x, coordinates[faces[i]->coordinates[3] - 1]->y);
                    glVertex3f(xPos + vertices[faces[i]->vertices[3] - 1]->x, yPos + vertices[faces[i]->vertices[3] - 1]->y, zPos + vertices[faces[i]->vertices[3] - 1]->z);
                    if (texture) glTexCoord2f(coordinates[faces[i]->coordinates[0] - 1]->x, coordinates[faces[i]->coordinates[0] - 1]->y);
                    glVertex3f(xPos + vertices[faces[i]->vertices[0] - 1]->x, yPos + vertices[faces[i]->vertices[0] - 1]->y, zPos + vertices[faces[i]->vertices[0] - 1]->z);
                    glEnd();

                } else {
                    glBegin(GL_TRIANGLE_STRIP);
                    for (int j = 0; j < (int) faces[i]->normals.size(); j++) {
                        glNormal3f(normals[faces[i]->normals[j] - 1]->x, normals[faces[i]->normals[j] - 1]->y, normals[faces[i]->normals[j] - 1]->z);
                    }

                    for (int j = 0; j < (int) faces[i]->vertices.size(); j++) {
                        if (texture) glTexCoord2f(coordinates[faces[i]->coordinates[j] - 1]->x, coordinates[faces[i]->coordinates[j] - 1]->y);
                        glVertex3f(xPos + vertices[faces[i]->vertices[j] - 1]->x, yPos + vertices[faces[i]->vertices[j] - 1]->y, zPos + vertices[faces[i]->vertices[j] - 1]->z);
                    }
                    glEnd();
                }

            }
            glPopMatrix();
        }
        ;
};

#endif
