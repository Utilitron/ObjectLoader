/*
 * camera.cc
 *
 *  Created on: May 24, 2014
 *      Author: Erik Ashcraft
 */

#include "camera.h"
const float TO_RADS = 3.141592654f / 180.0f; // The value of 1 degree in radians

Camera::Camera() {
	// Distance from our character
	radius = 15.0f;

	// Camera rotation
    xRot = 45.0f;
    yRot = 0.0f;
    zRot = 0.0f;

    // Camera position
    xPos = 0.0f;
    yPos = 0.0f;
    zPos = 0.0f;

    // Camera movement speed
    xSpeed = 0.0f;
    ySpeed = 0.0f;
    zSpeed = 0.0f;

    // How fast we move (higher values mean we move and  faster)
    velocity = 0.3f;

    moveForward = moveBackward = moveLeft = moveRight = false;
}

void Camera::move() {
	calculateCameraMovement();
    xPos += xSpeed;
    yPos += ySpeed;
    zPos += zSpeed;

    checkBoundries();
}

void Camera::calculateCameraMovement() {
    // Break up our movement along the X, Y and Z axis
    float movementX = 0.0f;
    float movementY = 0.0f;
    float movementZ = 0.0f;

    // Calculate our Y-Axis rotation in radians
    float yRotRad = toRads(yRot);

    float yRotRadSin = float(sin(yRotRad));
    float yRotRadCos = float(cos(yRotRad));

    if (moveForward == true) {
        movementX += (velocity * yRotRadSin);
        movementZ += (-velocity * yRotRadCos);
    }

    if (moveBackward == true) {
        movementX += ((-velocity/2) * yRotRadSin);
        movementZ += ((velocity/2) * yRotRadCos);
    }

    if (moveLeft == true) {
        movementX += ((-velocity/2) * yRotRadCos);
        movementZ += ((-velocity/2) * yRotRadSin);
    }

    if (moveRight == true) {
        movementX += ((velocity/2) * yRotRadCos);
        movementZ += ((velocity/2) * yRotRadSin);
    }


    // After combining our movements for any & all keys pressed, assign them to our camera speed along the given axis
    xSpeed = movementX;
    ySpeed = movementY;
    zSpeed = movementZ;
}

void Camera::checkBoundries() {
	//if (xPos > 14.0f) xPos = 14.0f;
	//if (xPos < -14.0f) xPos = -14.0f;
	//if (zPos > 14.0f) zPos = 14.0f;
	//if (zPos < -14.0f) zPos = -14.0f;
}

float Camera::toRads(const float &theAngleInDegrees) {
    return theAngleInDegrees * TO_RADS;
}


void Camera::setMoveForward(bool move){ moveForward = move; }
void Camera::setMoveBackward(bool move){ moveBackward = move; }
void Camera::setMoveLeft(bool move){ moveLeft = move; }
void Camera::setMoveRight(bool move){ moveRight = move; }


void Camera::setXrot(GLfloat rot){ xRot = rot; }
GLfloat Camera::getXrot(){ return xRot; }

void Camera::setYrot(GLfloat rot){ yRot = rot; }
GLfloat Camera::getYrot(){ return yRot; }

void Camera::setZrot(GLfloat rot){ zRot = rot; }
GLfloat Camera::getZrot(){ return zRot; }


void Camera::setXpos(GLfloat value) { this->xPos = value; }
GLfloat Camera::getXpos(){ return xPos; }

void Camera::setYpos(GLfloat value) { this->yPos = value; }
GLfloat Camera::getYpos(){ return yPos; }

void Camera::setZpos(GLfloat value) { this->zPos = value; }
GLfloat Camera::getZpos(){ return zPos; }


void Camera::setXspeed(GLfloat value) { this->ySpeed = value; }
GLfloat Camera::getXspeed() { return xSpeed; }

void Camera::setYspeed(GLfloat value) { this->xSpeed = value; }
GLfloat Camera::getYspeed() { return ySpeed; }

void Camera::setZspeed(GLfloat value) { this->zSpeed = value; }
GLfloat Camera::getZspeed() { return zSpeed; }


GLfloat Camera::getRadius(){ return radius; }
void Camera::setRadius(GLfloat rad){ radius = rad; }

GLfloat Camera::getVelocity(){ return velocity; }
