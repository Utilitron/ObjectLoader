/*
 * camera.h
 *
 *  Created on: May 24, 2014
 *      Author: Erik Ashcraft
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>

class Camera {
    private:
        void calculateCameraMovement();
        void checkBoundries();

    public:
        // Distance from our character
        GLfloat radius;

        // Camera rotation
        GLfloat xRot;
        GLfloat yRot;
        GLfloat zRot;

        // Camera position
        GLfloat xPos;
        GLfloat yPos;
        GLfloat zPos;

        // Camera movement speed
        GLfloat xSpeed;
        GLfloat ySpeed;
        GLfloat zSpeed;

        // How fast we move
        GLfloat velocity;

        // Hoding any keys down?
        bool moveForward;
        bool moveBackward;
        bool moveLeft;
        bool moveRight;

        Camera();

        void move();

        float toRads(const float &theAngleInDegrees);

        void setMoveForward(bool move);
        void setMoveBackward(bool move);
        void setMoveLeft(bool move);
        void setMoveRight(bool move);

        void setXrot(GLfloat value);
        GLfloat getXrot();

        void setYrot(GLfloat value);
        GLfloat getYrot();

        void setZrot(GLfloat value);
        GLfloat getZrot();

        void setXpos(GLfloat value);
        GLfloat getXpos();

        void setYpos(GLfloat value);
        GLfloat getYpos();

        void setZpos(GLfloat value);
        GLfloat getZpos();

        void setXspeed(GLfloat value);
        GLfloat getXspeed();

        void setYspeed(GLfloat value);
        GLfloat getYspeed();

        void setZspeed(GLfloat value);
        GLfloat getZspeed();

        void setRadius(GLfloat rad);
        GLfloat getRadius();

        GLfloat getVelocity();
};

#endif
