/*
 * moveable.h
 *
 *  Created on: Feb 09, 2014
 *      Author: Erik Ashcraft
 */

#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "drawable.h"

class Moveable: public Drawable {
    public:
        /**
         * move( x, y, z )
         * set the x, y and z positions the object
         *
         * @x   new x possition of the object
         * @y   new y possition of the object
         * @z   new z possition of the object
         **/
        void move(float x, float y, float z) {
            setXpos(x);
            setYpos(y);
            setZpos(z);
        }
        ;

};

#endif
