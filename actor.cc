/*
 * actor.cc
 *
 *  Created on: May 25, 2014
 *      Author: erik
 */

#include "actor.h"

Actor::Actor() {
    objectLoader = new ObjectLoader(this, "src/resources/VikingLoPol.obj");
}

Actor::~Actor() {

}

void Actor::draw() {
    // Set the default draw color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    drawObject(getXpos(), getYpos(), getZpos(), getXrot(), getYrot(), getZrot(), true);
}

void Actor::update() {
}
