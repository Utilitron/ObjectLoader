/*
 * drawable.h
 *
 *  Created on: Feb 08, 2014
 *      Author: Erik Ashcraft
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

#include "game_object.h"
#include "texture.h"

class Drawable: public GameObject {
    protected:
        float xPos, yPos, zPos, xRot, yRot, zRot;

        std::vector<Texture*> textures;

    public:
        /**
         * draw()
         * called to draw the object
         **/
        virtual void draw() = 0;

        /**
         * addTexture( texture )
         * set the texture the object
         *
         * @texture   new texture for the object
         **/
        void addTexture(Texture* texture) {
            this->textures.push_back(texture);
        }

        /**
         * setXpos( value )
         * set the x position the object
         *
         * @value   new x possition of the object
         **/
        void setXpos(float value) {
            this->xPos = value;
        }

        /**
         * getXpos()
         * get the x position the object
         **/
        float getXpos() {
            return xPos;
        }

        /**
         * setYpos( value )
         * set the y position the object
         *
         * @value   new y possition of the object
         **/
        void setYpos(float value) {
            this->yPos = value;
        }

        /**
         * getYpos()
         * get the y position the object
         **/
        float getYpos() {
            return yPos;
        }

        /**
         * setZpos( value )
         * set the z position the object
         *
         * @value   new z possition of the object
         **/
        void setZpos(float value) {
            this->zPos = value;
        }

        /**
         * getZpos()
         * get the z position the object
         **/
        float getZpos() {
            return zPos;
        }

        /**
         * setXrot( value )
         * set the x rotation the object
         *
         * @value   new x rotation of the object
         **/
        void setXrot(float value) {
            this->xRot = value;
        }

        /**
         * getXrot()
         * get the x rotation the object
         **/
        float getXrot() {
            return xRot;
        }

        /**
         * setYrot( value )
         * set the y rotation the object
         *
         * @value   new y rotation of the object
         **/
        void setYrot(float value) {
            this->yRot = value;
        }

        /**
         * getYrot()
         * get the y rotation the object
         **/
        float getYrot() {
            return yRot;
        }

        /**
         * setZrot( value )
         * set the z rotation the object
         *
         * @value   new z rotation of the object
         **/
        void setZrot(float value) {
            this->xRot = value;
        }

        /**
         * getZrot()
         * get the z rotation the object
         **/
        float getZrot() {
            return zRot;
        }
};

#endif
