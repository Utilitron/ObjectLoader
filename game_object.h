/*
 * game_object.h
 *
 *  Created on: Jan 11, 2014
 *      Author: Erik Ashcraft
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
    public:
        /**
         * update()
         * updated the game object with any data that may have changed
         */
        virtual void update() = 0;
};

#endif
