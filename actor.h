/*
 * actor.h
 *
 *  Created on: May 25, 2014
 *      Author: erik
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "glm/glm.hpp"
#include "object_loader.h"

#include "moveable.h"
#include "loadable.h"

class Actor: public Moveable, public Loadable {
    private:
        ObjectLoader* objectLoader;
        Loadable model;

    public:
        // Constructor with all the necessary parameters.
        Actor();
        ~Actor();

        /**
         * draw()
         * inherited from Drawable
         **/
        void draw();

        /**
         * update()
         * inherited from GameObject
         **/
        void update();
};

#endif
